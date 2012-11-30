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

#include "UBTeacherGuideEditionWidget.h"
#include "globals/UBGlobals.h"
#include "UBTGMediaWidget.h"
#include "UBTGActionWidget.h"
#include "UBTGUrlWidget.h"

UBTeacherGuideEditionWidget::UBTeacherGuideEditionWidget(UBTGModel* pModel, QWidget *parent, const char* name) :
    QWidget(parent)
  , mpLayout(NULL)
  , mpDocumentTitle(NULL)
  , mpPageNumberLabel(NULL)
  , mpPageTitle(NULL)
  , mpComment(NULL)
  , mpSeparator(NULL)
  , mpTreeWidget(NULL)
  , mpRootWidgetItem(NULL)
  , mpAddAnActionItem(NULL)
  , mpAddAMediaItem(NULL)
  , mpAddALinkItem(NULL)
  , mpModel(pModel)
{
    setObjectName(name);

    mpLayout = new QVBoxLayout(this);
    mpPageNumberLabel = new QLabel(this);
    mpPageNumberLabel->setAlignment(Qt::AlignRight);
    mpPageNumberLabel->setObjectName("UBTGPageNumberLabel");
    mpLayout->addWidget(mpPageNumberLabel);
    // tree basic configuration


//    if (UBSettings::settings()->teacherGuidePageZeroActivated->get().toBool()) {
//        mpDocumentTitle = new QLabel(this);
//        mpDocumentTitle->setObjectName("UBTGPresentationDocumentTitle");
//        mpLayout->addWidget(mpDocumentTitle);
//    }

    mpPageTitle = new UBTGAdaptableText(0, this);
    mpPageTitle->setObjectName("UBTGEditionPageTitle");
    mpPageTitle->setPlaceHolderText(tr("Type title here ..."));
    mpLayout->addWidget(mpPageTitle);

    mpComment = new UBTGAdaptableText(0, this);
    mpComment->setObjectName("UBTGEditionComment");
    mpComment->setPlaceHolderText(tr("Type comment here ..."));
    mpLayout->addWidget(mpComment);

    mpSeparator = new QFrame(this);
    mpSeparator->setObjectName("UBTGSeparator");
    mpSeparator->setFixedHeight(UBTG_SEPARATOR_FIXED_HEIGHT);
    mpLayout->addWidget(mpSeparator);

    mpTreeWidget = new QTreeWidget(this);
    mpTreeWidget->setStyleSheet("selection-background-color:transparent; padding-bottom:5px; padding-top:5px;");
    mpLayout->addWidget(mpTreeWidget);

    mpRootWidgetItem = mpTreeWidget->invisibleRootItem();
    mpTreeWidget->setRootIsDecorated(false);
    mpTreeWidget->setIndentation(0);
    mpTreeWidget->setDropIndicatorShown(false);
    mpTreeWidget->header()->close();
    mpTreeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpTreeWidget->setColumnCount(2);
    mpTreeWidget->header()->setStretchLastSection(false);
    mpTreeWidget->header()->setResizeMode(0, QHeaderView::Stretch);
    mpTreeWidget->header()->setResizeMode(1, QHeaderView::Fixed);
    mpTreeWidget->header()->setDefaultSectionSize(18);
    mpTreeWidget->setSelectionMode(QAbstractItemView::NoSelection);

    connect(mpTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onAddItemClicked(QTreeWidgetItem*,int)));
    //connect(UBApplication::boardController, SIGNAL(activeSceneChanged()), this, SLOT(onActiveSceneChanged()));

#ifdef Q_WS_MAC
    // on mac and with the custom qt the widget on the tree are not automatically relocated when using the vertical scrollbar. To relocate them we link the valueChange signal of the vertical scrollbar witht a local signal to trig a change and a repaint of the tree widget
    connect(mpTreeWidget->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(onSliderMoved(int)));
#endif

    mpAddAnActionItem = new UBAddItem(tr("Add an action"), eUBTGAddSubItemWidgetType_Action, mpTreeWidget);
    mpAddAMediaItem = new UBAddItem(tr("Add a media"), eUBTGAddSubItemWidgetType_Media, mpTreeWidget);
    mpAddALinkItem = new UBAddItem(tr("Add a link"), eUBTGAddSubItemWidgetType_Url, mpTreeWidget);

    mpRootWidgetItem->addChild(mpAddAnActionItem);
    mpRootWidgetItem->addChild(mpAddAMediaItem);
    mpRootWidgetItem->addChild(mpAddALinkItem);

//    if (UBSettings::settings()->teacherGuideLessonPagesActivated->get().toBool()) {
//        UBSvgSubsetAdaptor::addElementToBeStored(QString("teacherGuide"), this);
//        //connect(UBApplication::boardController, SIGNAL(documentSet(UBDocumentProxy*)), this, SLOT(onActiveDocumentChanged()));
//    }
}

UBTeacherGuideEditionWidget::~UBTeacherGuideEditionWidget()
{
    DELETEPTR(mpDocumentTitle);
    DELETEPTR(mpPageNumberLabel);
    DELETEPTR(mpPageTitle);
    DELETEPTR(mpComment);
    DELETEPTR(mpSeparator);
    DELETEPTR(mpAddAnActionItem);
    DELETEPTR(mpAddAMediaItem);
    DELETEPTR(mpAddALinkItem);
    DELETEPTR(mpTreeWidget);
    DELETEPTR(mpLayout);
}

#ifdef Q_WS_MAC
void UBTeacherGuideEditionWidget::onSliderMoved(int size)
{
    Q_UNUSED(size);
    if(mpAddAMediaItem)
        mpAddAMediaItem->setExpanded(true);
}
#endif
void UBTeacherGuideEditionWidget::showEvent(QShowEvent* event)
{
    setFocus();
    QWidget::showEvent(event);
}

void UBTeacherGuideEditionWidget::onActiveDocumentChanged()
{
//    int activeSceneIndex = UBApplication::boardController->activeSceneIndex();
//    if (UBApplication::boardController->pageFromSceneIndex(activeSceneIndex) != 0)
//        load(UBSvgSubsetAdaptor::readTeacherGuideNode(activeSceneIndex));
}

void UBTeacherGuideEditionWidget::load(QString element)
{
    cleanData();
    QDomDocument doc("TeacherGuide");
    doc.setContent(element);

    for (QDomElement element = doc.documentElement().firstChildElement();
         !element.isNull(); element = element.nextSiblingElement()) {
        QString tagName = element.tagName();
        if (tagName == "title")
            mpPageTitle->setInitialText(element.attribute("value"));
        else if (tagName == "comment")
            mpComment->setInitialText(element.attribute("value"));
        else if (tagName == "media")
            onAddItemClicked(mpAddAMediaItem, 0, &element);
        else if (tagName == "link")
            onAddItemClicked(mpAddALinkItem, 0, &element);
        else if (tagName == "action")
            onAddItemClicked(mpAddAnActionItem, 0, &element);
    }
}

QVector<tIDataStorage*> UBTeacherGuideEditionWidget::save(int pageIndex)
{
    QVector<tIDataStorage*> result;
//    if (pageIndex != UBApplication::boardController->currentPage())
//        return result;
    tIDataStorage* data = new tIDataStorage();
    data->name = "teacherGuide";
    data->type = eElementType_START;
    data->attributes.insert("version", "2.00");
    result << data;

    data = new tIDataStorage();
    data->name = "title";
    data->type = eElementType_UNIQUE;
    data->attributes.insert("value", mpPageTitle->text());
    if (mpPageTitle->text().length())
        result << data;

    data = new tIDataStorage();
    data->name = "comment";
    data->type = eElementType_UNIQUE;
    data->attributes.insert("value", mpComment->text());
    if (mpComment->text().length())
        result << data;

    QList<QTreeWidgetItem*> children = getChildrenList(mpAddAnActionItem);
    children << getChildrenList(mpAddAMediaItem);
    children << getChildrenList(mpAddALinkItem);

    foreach(QTreeWidgetItem* widgetItem, children) {
//        tUBGEElementNode* node = dynamic_cast<iUBTGSaveData*>(mpTreeWidget->itemWidget( widgetItem, 0))->saveData();
//        if (node) {
//            data = new tIDataStorage();
//            data->name = node->name;
//            data->type = eElementType_UNIQUE;
//            foreach(QString currentKey, node->attributes.keys())
//                data->attributes.insert(currentKey, node->attributes.value(currentKey));
//            result << data;
//        }
    }

    data = new tIDataStorage();
    data->name = "teacherGuide";
    data->type = eElementType_END;
    result << data;
    return result;
}

void UBTeacherGuideEditionWidget::onActiveSceneChanged()
{
//    int currentPage = UBApplication::boardController->currentPage();
//    if (currentPage > 0) {
//        cleanData();
//        load( UBSvgSubsetAdaptor::readTeacherGuideNode( UBApplication::boardController->activeSceneIndex()));
//        mpPageNumberLabel->setText(tr("Page: %0").arg(currentPage));
//        UBDocumentProxy* documentProxy = UBApplication::boardController->selectedDocument();
//        if (mpDocumentTitle)
//            mpDocumentTitle->setText(documentProxy->metaData(UBSettings::sessionTitle).toString());
//    }
}

void UBTeacherGuideEditionWidget::cleanData()
{
    mpPageTitle->setText("");
    mpComment->setText("");
    QList<QTreeWidgetItem*> children = mpAddAnActionItem->takeChildren();
    children << mpAddAMediaItem->takeChildren();
    children << mpAddALinkItem->takeChildren();

    foreach(QTreeWidgetItem* item, children) {
        DELETEPTR(item);
    }
}

QList<QTreeWidgetItem*> UBTeacherGuideEditionWidget::getChildrenList( QTreeWidgetItem* widgetItem)
{
    QList<QTreeWidgetItem*> result;
    for (int i = 0; i < widgetItem->childCount(); i += 1)
        result << widgetItem->child(i);
    return result;
}

QVector<tUBGEElementNode*> UBTeacherGuideEditionWidget::getPageAndCommentData()
{
    QVector<tUBGEElementNode*> result;
    tUBGEElementNode* pageTitle = new tUBGEElementNode();
    pageTitle->name = "pageTitle";
    pageTitle->attributes.insert("value", mpPageTitle->text());
    result << pageTitle;

    tUBGEElementNode* comment = new tUBGEElementNode();
    comment->name = "comment";
    comment->attributes.insert("value", mpComment->text());
    result << comment;
    return result;
}

QVector<tUBGEElementNode*> UBTeacherGuideEditionWidget::getData()
{
    QVector<tUBGEElementNode*> result;
    QList<QTreeWidgetItem*> children = getChildrenList(mpAddAnActionItem);
    children << getChildrenList(mpAddAMediaItem);
    children << getChildrenList(mpAddALinkItem);
    result << getPageAndCommentData();
//    foreach(QTreeWidgetItem* widgetItem, children) {
//        tUBGEElementNode* node = dynamic_cast<iUBTGSaveData*>(mpTreeWidget->itemWidget( widgetItem, 0))->saveData();
//        if (node)
//            result << node;
//    }
    return result;
}

void UBTeacherGuideEditionWidget::onAddItemClicked(QTreeWidgetItem* widget, int column, QDomElement *element)
{
    int addSubItemWidgetType = widget->data(column, Qt::UserRole).toInt();
    if (addSubItemWidgetType != eUBTGAddSubItemWidgetType_None) {
        QTreeWidgetItem* newWidgetItem = new QTreeWidgetItem(widget);
        newWidgetItem->setData(column, Qt::UserRole, eUBTGAddSubItemWidgetType_None);
        newWidgetItem->setData(1, Qt::UserRole, eUBTGAddSubItemWidgetType_None);
        newWidgetItem->setIcon(1, QIcon(":images/close.svg"));

        switch (addSubItemWidgetType) {
        case eUBTGAddSubItemWidgetType_Action: {
            UBTGActionWidget* actionWidget = new UBTGActionWidget(widget);
            if (element)
                actionWidget->initializeWithDom(*element);
            mpTreeWidget->setItemWidget(newWidgetItem, 0, actionWidget);
            break;
        }
        case eUBTGAddSubItemWidgetType_Media: {
            UBTGMediaWidget* mediaWidget = new UBTGMediaWidget(widget);
            if (element)
                mediaWidget->initializeWithDom(*element);
            mpTreeWidget->setItemWidget(newWidgetItem,0, mediaWidget);
            break;
        }
        case eUBTGAddSubItemWidgetType_Url: {
            UBTGUrlWidget* urlWidget = new UBTGUrlWidget();
            if (element)
                urlWidget->initializeWithDom(*element);
            mpTreeWidget->setItemWidget(newWidgetItem, 0, urlWidget);
            break;
        }
        default:
            delete newWidgetItem;
            qCritical() << "onAddItemClicked no action set";
            return;
        }

        if (addSubItemWidgetType != eUBTGAddSubItemWidgetType_None && !widget->isExpanded())
            widget->setExpanded(true);
        else {
            //to update the tree and subtrees
            widget->setExpanded(false);
            widget->setExpanded(true);
        }
    }
    else if (column == 1 && addSubItemWidgetType == eUBTGAddSubItemWidgetType_None) {
        UBTGMediaWidget* media = dynamic_cast<UBTGMediaWidget*>(mpTreeWidget->itemWidget(widget, 0));
        if (media)
            media->removeSource();
        int index = mpTreeWidget->currentIndex().row();
        QTreeWidgetItem* toBeDeletedWidgetItem = widget->parent()->takeChild(index);
        delete toBeDeletedWidgetItem;
    }
}

bool UBTeacherGuideEditionWidget::isModified()
{
    bool result = false;
    result |= mpPageTitle->text().length() > 0;
    result |= mpComment->text().length() > 0;
    result |= mpAddAnActionItem->childCount() > 0;
    result |= mpAddAMediaItem->childCount() > 0;
    result |= mpAddALinkItem->childCount() > 0;
    return result;
}
