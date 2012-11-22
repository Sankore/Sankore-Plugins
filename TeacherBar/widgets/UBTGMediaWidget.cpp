/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QFileInfo>
#include <QWebFrame>

#include "UBTGMediaWidget.h"
#include "globals/UBGlobals.h"
#include "frameworks/UBFileSystemUtils.h"

UBTGMediaWidget::UBTGMediaWidget(QTreeWidgetItem* widget, QWidget* parent,const char* name): QStackedWidget(parent)
  , mpTreeWidgetItem(widget)
  , mpDropMeWidget(NULL)
  , mpWorkWidget(NULL)
  , mpLayout(NULL)
  , mpMediaLayout(NULL)
  , mpTitle(NULL)
  , mpMediaLabelWidget(NULL)
  , mpMediaWidget(NULL)
  , mpWebView(NULL)
  , mMediaPath(QString(""))
  , mIsPresentationMode(false)
  , mIsInitializationMode(false)
  , mMediaWidgetHeight(150)
{
    setObjectName(name);
    mpDropMeWidget = new QLabel();
    mpDropMeWidget->setObjectName("UBTGMediaDropMeLabel");
    mpDropMeWidget->setText(tr("drop media here ..."));
    mpDropMeWidget->setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    addWidget(mpDropMeWidget);

    setMinimumHeight(250);
}

UBTGMediaWidget::UBTGMediaWidget(QString mediaFolder, QString mediaPath, QTreeWidgetItem* widget, QWidget* parent,bool forceFlashMediaType,const char* name): QStackedWidget(parent)
  , mpTreeWidgetItem(widget)
  , mpDropMeWidget(NULL)
  , mpWorkWidget(NULL)
  , mpLayout(NULL)
  , mpMediaLayout(NULL)
  , mpTitle(NULL)
  , mpMediaLabelWidget(NULL)
  , mpMediaWidget(NULL)
  , mpWebView(NULL)
  , mIsPresentationMode(true)
  , mMediaType("")
  , mIsInitializationMode(false)
  , mMediaWidgetHeight(150)
{
    setObjectName(name);
    //mMediaPath = UBApplication::boardController->selectedDocument()->persistencePath()+ "/" + mediaPath;
    // TODO: give the complete path while doing the instanciation!
    mMediaPath = mediaPath;
    mMediaFolder = mediaFolder;
    setAcceptDrops(false);
    createWorkWidget(forceFlashMediaType);
    setFixedHeight(200);
}

UBTGMediaWidget::~UBTGMediaWidget()
{
    DELETEPTR(mpTitle);
    DELETEPTR(mpMediaLabelWidget);
    DELETEPTR(mpMediaWidget);
    DELETEPTR(mpWebView);
    DELETEPTR(mpMediaLayout);
    DELETEPTR(mpLayout);

    removeWidget(mpDropMeWidget);
    DELETEPTR(mpDropMeWidget);
    removeWidget(mpWorkWidget);
    DELETEPTR(mpWorkWidget);
}

void UBTGMediaWidget::initializeWithDom(QDomElement element)
{
    mIsInitializationMode = true;
    setAcceptDrops(false);
    // No need for that because mMediaPath is initialized in UBTGMediaWidget's constructor
    //mMediaPath = UBApplication::boardController->selectedDocument()->persistencePath() + "/" + element.attribute("relativePath");
    mMediaPath = element.attribute("relativePath");
    createWorkWidget(element.attribute("mediaType").contains("flash"));
    setFixedHeight(200);
    mpTitle->setInitialText(element.attribute("title"));
    mIsInitializationMode = false;
}

void UBTGMediaWidget::removeSource()
{
    QFileInfo fileInfo(mMediaFolder + "/" + mMediaPath);
    if(fileInfo.isFile())
        QFile(mMediaFolder + "/" + mMediaPath).remove();
    else
        UBFileSystemUtils::deleteDir(mMediaFolder + "/" + mMediaPath);
}

void UBTGMediaWidget::hideEvent(QHideEvent* event)
{
    if(mpWebView)
        mpWebView->page()->mainFrame()->setContent("Hidden widget"/*UBGraphicsW3CWidgetItem::freezedWidgetPage().toAscii()*/);
    QWidget::hideEvent(event);
}

void UBTGMediaWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    if(mpWebView){
        QString indexPath = mMediaFolder + mMediaPath+"/index.htm";
        if(!QFile::exists(indexPath))
            indexPath += "l";
        mpWebView->load(QUrl::fromLocalFile(indexPath));
    }
}

tUBGEElementNode* UBTGMediaWidget::saveData()
{
    if(!mpTitle)
        return 0;
    tUBGEElementNode* result = new tUBGEElementNode();
    QString relativePath = "/" + mMediaPath;
    //relativePath = relativePath.replace(UBApplication::boardController->selectedDocument()->persistencePath()+"/","");
    result->name = "media";
    result->attributes.insert("title",mpTitle->text());
    result->attributes.insert("relativePath",relativePath);
    result->attributes.insert("mediaType",mMediaType);
    return result;
}

void UBTGMediaWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void UBTGMediaWidget::createWorkWidget(bool forceFlashMediaType)
{
    QString mimeType = UBFileSystemUtils::mimeTypeFromFileName(mMediaPath);
    bool setMedia = true;
    //UBDocumentProxy* proxyDocument = UBApplication::boardController->selectedDocument();
    if(mimeType.contains("audio") || mimeType.contains("video")){
        mMediaType = mimeType.contains("audio")? "audio":"movie";
        mpMediaWidget = new UBMediaWidget(mimeType.contains("audio")?eMediaType_Audio:eMediaType_Video);
        if(mIsPresentationMode || mIsInitializationMode){
            mpMediaWidget->setFile(mMediaPath);
        }
        else{
            // No! Do something generic instead!
            //mMediaPath = UBPersistenceManager::persistenceManager()->addObjectToTeacherGuideDirectory(proxyDocument, mMediaPath);
            mpMediaWidget->setFile(mMediaPath);
        }
    }
    else if(mimeType.contains("image")){
        mMediaType = "image";
        if(!(mIsPresentationMode || mIsInitializationMode)){
            // No! Do something generic instead!
            //mMediaPath = UBPersistenceManager::persistenceManager()->addObjectToTeacherGuideDirectory(proxyDocument, mMediaPath);
        }
        mpMediaLabelWidget = new QLabel();
        QPixmap pixmap = QPixmap(mMediaPath);
        pixmap = pixmap.scaledToHeight(mMediaWidgetHeight);
        mpMediaLabelWidget->setPixmap(pixmap);
    }
    else if(mimeType.contains("widget") && !forceFlashMediaType){
        mMediaType = "w3c";
        if(!(mIsPresentationMode || mIsInitializationMode)){
            // No! Do something generic instead!
            //mMediaPath = UBPersistenceManager::persistenceManager()->addWidgetToTeacherGuideDirectory(proxyDocument, mMediaPath);
        }
        mpWebView = new UBDraggableWeb(mMediaPath);
        mpWebView->setAcceptDrops(false);
        mpWebView->settings()->setAttribute(QWebSettings::JavaEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
        mpWebView->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
        QString indexPath = mMediaPath+"/index.htm";
        if(!QFile::exists(indexPath))
            indexPath += "l";
        mpWebView->load(QUrl::fromLocalFile(indexPath));
    }
    else if(mimeType.contains("x-shockwave-flash") || forceFlashMediaType){
        mMediaType = "flash";
        if(!(mIsPresentationMode || mIsInitializationMode)){
            // No! Do something generic instead!
            //QDir baseW3CDirectory(UBPersistenceManager::persistenceManager()->teacherGuideAbsoluteObjectPath(proxyDocument));
            //mMediaPath = UBGraphicsW3CWidgetItem::createNPAPIWrapperInDir(mMediaPath,baseW3CDirectory,mimeType,QSize(100,100),QUuid::createUuid());
        }
        qDebug() << mMediaPath;
        mpWebView = new UBDraggableWeb(mMediaPath);
        mpWebView->setAcceptDrops(false);
        mpWebView->settings()->setAttribute(QWebSettings::JavaEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
        mpWebView->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
        mpWebView->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);
        QString indexPath = mMediaPath+"/index.htm";
        if(!QFile::exists(indexPath))
            indexPath += "l";
        mpWebView->load(QUrl::fromLocalFile(indexPath));
    }
    else{
        qDebug() << "createWorkWidget mime type not handled" << mimeType;
        setMedia=false;
    }

    if(setMedia){
        setAcceptDrops(false);
        mpWorkWidget = new QWidget(this);
        if(!mIsPresentationMode){
            mpLayout = new QVBoxLayout(mpWorkWidget);
            mpTitle = new UBTGAdaptableText(mpTreeWidgetItem,mpWorkWidget);
            mpTitle->setPlaceHolderText(tr("Type title here..."));
            mpLayout->addWidget(mpTitle);
            mpMediaLayout = new QHBoxLayout;
            mpLayout->addLayout(mpMediaLayout);
            mpWorkWidget->setLayout(mpLayout);
        }
        else{
            mpMediaLayout = new QHBoxLayout(mpWorkWidget);
            mpWorkWidget->setLayout(mpMediaLayout);
        }

        mpMediaLayout->addStretch(1);

        if(mpMediaLabelWidget){
            mpMediaLabelWidget->setFixedHeight(mMediaWidgetHeight);
            mpMediaLabelWidget->setParent(mpWorkWidget);
            mpMediaLayout->addWidget(mpMediaLabelWidget);
        }
        else if (mpMediaWidget){
            mpMediaWidget->setFixedHeight(mMediaWidgetHeight);
            mpMediaWidget->setParent(mpWorkWidget);
            mpMediaLayout->addWidget(mpMediaWidget);
        }
        else if (mpWebView){
            mpWebView->setFixedHeight(mMediaWidgetHeight);
            mpWebView->setParent(mpWorkWidget);
            mpMediaLayout->addWidget(mpWebView);
            mpWebView->show();
        }
        mpMediaLayout->addStretch(1);
        addWidget(mpWorkWidget);
        setCurrentWidget(mpWorkWidget);
        mpWorkWidget->show();

    }
}

void UBTGMediaWidget::parseMimeData(const QMimeData* pMimeData)
{
    if(pMimeData){
        if(pMimeData->hasText()){
            mMediaPath = QUrl::fromLocalFile(pMimeData->text()).toString();
        }
        else if(pMimeData->hasUrls()){
            mMediaPath = pMimeData->urls().at(0).toString();
        }
        else if(pMimeData->hasImage()){
            qDebug() << "Not yet implemented";
        }
    }
    else
        qDebug() << "No mime data present";

    createWorkWidget();
}

void UBTGMediaWidget::dropEvent(QDropEvent* event)
{
    parseMimeData(event->mimeData());
    event->accept();
}

void UBTGMediaWidget::mousePressEvent(QMouseEvent *event)
{
    if (!mIsPresentationMode)
        event->ignore();
    else{
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        QList<QUrl> urlList;
#ifdef Q_WS_WIN
        urlList << QUrl::fromLocalFile(mMediaPath);
#else
        urlList << QUrl(mMediaPath);
#endif
        mimeData->setUrls(urlList);
        drag->setMimeData(mimeData);

        drag->exec();
        event->accept();
    }
}
