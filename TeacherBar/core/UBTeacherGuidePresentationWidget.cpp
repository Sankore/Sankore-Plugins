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
#include <QHeaderView>
#include <QApplication>

#include "UBTeacherGuidePresentationWidget.h"
#include "globals/UBGlobals.h"
#include "UBTGMediaWidget.h"

UBTeacherGuidePresentationWidget::UBTeacherGuidePresentationWidget(UBTGModel* pModel, QWidget *parent, const char *name) :
    QWidget(parent)
  , mpPageTitle(NULL)
  , mpComment(NULL)
  , mpLayout(NULL)
  , mpButtonTitleLayout(NULL)
  , mpDocumentTitle(NULL)
  , mpPageNumberLabel(NULL)
  , mpSeparator(NULL)
  , mpModePushButton(NULL)
  , mpTreeWidget(NULL)
  , mpRootWidgetItem(NULL)
  , mpMediaSwitchItem(NULL)
  , mpModel(pModel)
{
    setObjectName(name);

    mpLayout = new QVBoxLayout(this);
    setLayout(mpLayout);
    mpPageNumberLabel = new QLabel(this);
    mpPageNumberLabel->setAlignment(Qt::AlignRight);
    mpPageNumberLabel->setObjectName("UBTGPageNumberLabel");

    mpLayout->addWidget(mpPageNumberLabel);

    mpButtonTitleLayout = new QHBoxLayout(0);

    mpModePushButton = new QPushButton(this);
    mpModePushButton->setIcon(QIcon(":images/teacherGuide/pencil.svg"));
    mpModePushButton->setMaximumWidth(32);
    mpModePushButton->installEventFilter(this);

    connect(mpModePushButton, SIGNAL(clicked()), parentWidget(), SLOT(changeMode()));
    mpButtonTitleLayout->addWidget(mpModePushButton);

//    if (UBSettings::settings()->teacherGuidePageZeroActivated->get().toBool()) {
//        mpDocumentTitle = new QLabel(this);
//        mpDocumentTitle->setObjectName("UBTGPresentationDocumentTitle");
//        mpButtonTitleLayout->addWidget(mpDocumentTitle);
//    }

    mpLayout->addLayout(mpButtonTitleLayout);

    mpPageTitle = new UBTGAdaptableText(0, this);
    mpPageTitle->setObjectName("UBTGPresentationPageTitle");
    mpPageTitle->setReadOnly(true);
    mpPageTitle->setStyleSheet("background-color:transparent");
    mpLayout->addWidget(mpPageTitle);

    mpComment = new UBTGAdaptableText(0, this);
    mpComment->setObjectName("UBTGPresentationComment");
    mpComment->setReadOnly(true);
    mpComment->setStyleSheet("background-color:transparent");
    mpLayout->addWidget(mpComment);

    mpSeparator = new QFrame(this);
    mpSeparator->setFixedHeight(UBTG_SEPARATOR_FIXED_HEIGHT);
    mpSeparator->setObjectName("UBTGSepartor");
    mpLayout->addWidget(mpSeparator);

    mpTreeWidget = new UBTGDraggableTreeItem(this);
    mpLayout->addWidget(mpTreeWidget);

    mpRootWidgetItem = mpTreeWidget->invisibleRootItem();
    mpTreeWidget->setDragEnabled(true);
    mpTreeWidget->setRootIsDecorated(false);
    mpTreeWidget->setIndentation(0);
    mpTreeWidget->setDropIndicatorShown(false);
    mpTreeWidget->header()->close();
    mpTreeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpTreeWidget->setStyleSheet("selection-background-color:transparent; padding-bottom:5px; padding-top:5px; ");
    mpTreeWidget->setIconSize(QSize(24,24));
    connect(mpTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onAddItemClicked(QTreeWidgetItem*,int)));
    //connect(UBApplication::boardController, SIGNAL(activeSceneChanged()), this, SLOT(onActiveSceneChanged()));
#ifdef Q_WS_MAC
    // on mac and with the custom qt the widget on the tree are not automatically relocated when using the vertical scrollbar. To relocate them we link the valueChange signal of the vertical scrollbar witht a local signal to trig a change and a repaint of the tree widget
    connect(mpTreeWidget->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onSliderMoved(int)));
#endif
}

UBTeacherGuidePresentationWidget::~UBTeacherGuidePresentationWidget()
{
    DELETEPTR(mpComment);
    DELETEPTR(mpPageTitle);
    DELETEPTR(mpPageNumberLabel);
    DELETEPTR(mpSeparator);
    DELETEPTR(mpMediaSwitchItem);
    DELETEPTR(mpModePushButton);
    DELETEPTR(mpDocumentTitle);
    DELETEPTR(mpButtonTitleLayout);
    DELETEPTR(mpTreeWidget);
    DELETEPTR(mpLayout);
}

#ifdef Q_WS_MAC
void UBTeacherGuidePresentationWidget::onSliderMoved(int size)
{
    Q_UNUSED(size);
    if(mpMediaSwitchItem)
        mpMediaSwitchItem->setExpanded(true);
}
#endif

bool UBTeacherGuidePresentationWidget::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object);
    if (event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverMove || event->type() == QEvent::HoverLeave)
        return true;
    return false;
}

void UBTeacherGuidePresentationWidget::cleanData()
{
    mpPageTitle->showText("");
    mpComment->showText("");
    //tree clean
    QList<QTreeWidgetItem*> itemToRemove = mpRootWidgetItem->takeChildren();
    foreach(QTreeWidgetItem* eachItem, itemToRemove) {
        DELETEPTR(eachItem);
    }
    // the mpMediaSwitchItem is deleted by the previous loop but the pointer is not set to zero
    mpMediaSwitchItem = NULL;
}

void UBTeacherGuidePresentationWidget::onActiveSceneChanged()
{
//    cleanData();
//    mpPageNumberLabel->setText(tr("Page: %0").arg(UBApplication::boardController->currentPage()));
//    UBDocumentProxy* documentProxy = UBApplication::boardController->selectedDocument();
//    if (mpDocumentTitle)
//        mpDocumentTitle->setText( documentProxy->metaData(UBSettings::sessionTitle).toString());
}

void UBTeacherGuidePresentationWidget::createMediaButtonItem()
{
    if (!mpMediaSwitchItem) {
        mpMediaSwitchItem = new QTreeWidgetItem(mpRootWidgetItem);
        mpMediaSwitchItem->setText(0, "+");
        mpMediaSwitchItem->setExpanded(false);
        mpMediaSwitchItem->setData(0, tUBTGTreeWidgetItemRole_HasAnAction, tUBTGActionAssociateOnClickItem_EXPAND);
        mpMediaSwitchItem->setData(0, Qt::BackgroundRole, QVariant(QColor(200, 200, 200)));
        mpMediaSwitchItem->setData(0, Qt::FontRole, QVariant(QFont(QApplication::font().family(), 16)));
        mpMediaSwitchItem->setData(0, Qt::TextAlignmentRole, QVariant(Qt::AlignCenter));
        mpRootWidgetItem->addChild(mpMediaSwitchItem);
    }
}

void UBTeacherGuidePresentationWidget::showData( QVector<tUBGEElementNode*> data)
{
    cleanData();

    foreach(tUBGEElementNode* element, data) {
        if (element->name == "pageTitle")
            mpPageTitle->showText(element->attributes.value("value"));
        else if (element->name == "comment")
            mpComment->showText(element->attributes.value("value"));
        else if (element->name == "action") {
            QTreeWidgetItem* newWidgetItem = new QTreeWidgetItem(mpRootWidgetItem);
            newWidgetItem->setText(0, element->attributes.value("task"));
            newWidgetItem->setFlags(Qt::ItemIsEnabled);
            QString colorString = element->attributes.value("owner").toInt() == 0 ? "blue" : "green";
            UBTGAdaptableText* textWidget = new UBTGAdaptableText(newWidgetItem, 0);
            textWidget->bottomMargin(14);
            textWidget->setStyleSheet( "QWidget {background: #EEEEEE; border:none; color:" + colorString + ";}");
            textWidget->showText(element->attributes.value("task"));
            textWidget->document()->setDefaultFont( QFont(QApplication::font().family(), 11));
            mpTreeWidget->setItemWidget(newWidgetItem, 0, textWidget);

            mpRootWidgetItem->addChild(newWidgetItem);
        }
        else if (element->name == "media") {
            createMediaButtonItem();
            QTreeWidgetItem* newWidgetItem = new QTreeWidgetItem(mpMediaSwitchItem);
            newWidgetItem->setIcon(0, QIcon( ":images/teacherGuide/" + element->attributes.value("mediaType") + "_24x24.svg"));
            newWidgetItem->setText(0, element->attributes.value("title"));
            newWidgetItem->setData(0, tUBTGTreeWidgetItemRole_HasAnAction, tUBTGActionAssociateOnClickItem_MEDIA);
            newWidgetItem->setData(0, Qt::FontRole, QVariant(QFont(QApplication::font().family(), 11)));
            QString mimeTypeString;
#ifdef Q_WS_WIN
            mimeTypeString = QUrl::fromLocalFile(UBApplication::boardController->selectedDocument()->persistencePath()+ "/" + element->attributes.value("relativePath")).toString();
#else
            //mimeTypeString = UBApplication::boardController->selectedDocument()->persistencePath() + "/" + element->attributes.value("relativePath");
#endif
            newWidgetItem->setData(0, TG_USER_ROLE_MIME_TYPE, mimeTypeString);
            newWidgetItem->setFlags( Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            mpRootWidgetItem->addChild(newWidgetItem);

            QTreeWidgetItem* mediaItem = new QTreeWidgetItem(newWidgetItem);
            mediaItem->setData(0, tUBTGTreeWidgetItemRole_HasAnAction, tUBTGActionAssociateOnClickItem_NONE);
//            UBTGMediaWidget* mediaWidget = new UBTGMediaWidget(element->attributes.value("relativePath"), newWidgetItem,0,element->attributes.value("mediaType").contains("flash"));
//            newWidgetItem->setExpanded(false);
//            mpTreeWidget->setItemWidget(mediaItem, 0, mediaWidget);
        }
        else if (element->name == "link") {
            createMediaButtonItem();
            QTreeWidgetItem* newWidgetItem = new QTreeWidgetItem( mpMediaSwitchItem);
            newWidgetItem->setIcon(0, QIcon(":images/teacherGuide/link_24x24.svg"));
            newWidgetItem->setText(0, element->attributes.value("title"));
            newWidgetItem->setData(0, tUBTGTreeWidgetItemRole_HasAnAction, tUBTGActionAssociateOnClickItem_URL);
            newWidgetItem->setData(0, tUBTGTreeWidgetItemRole_HasAnUrl, QVariant(element->attributes.value("url")));
            newWidgetItem->setData(0, Qt::FontRole, QVariant(QFont(QApplication::font().family(), 11)));
            newWidgetItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            mpRootWidgetItem->addChild(newWidgetItem);
        }
    }
}

void UBTeacherGuidePresentationWidget::onAddItemClicked(QTreeWidgetItem* widget, int column)
{
    int associateAction = widget->data(column, tUBTGTreeWidgetItemRole_HasAnAction).toInt();
    if (column == 0 && associateAction != tUBTGActionAssociateOnClickItem_NONE) {
        switch (associateAction) {
        case tUBTGActionAssociateOnClickItem_EXPAND:
            widget->setExpanded(!widget->isExpanded());
            if (widget->isExpanded())
                mpMediaSwitchItem->setText(0, "-");
            else
                mpMediaSwitchItem->setText(0, "+");
            break;
        case tUBTGActionAssociateOnClickItem_URL:
            widget->data(column, tUBTGTreeWidgetItemRole_HasAnUrl).toString();
            //UBApplication::webController->loadUrl( QUrl( widget->data(column, tUBTGTreeWidgetItemRole_HasAnUrl).toString()));
            break;
        case tUBTGActionAssociateOnClickItem_MEDIA:
            widget->setExpanded(!widget->isExpanded());
            break;
        default:
            qDebug() << "associateAction no action set " << associateAction;
        }
    }
}
