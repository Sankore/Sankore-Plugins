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
#ifndef UBTEACHERGUIDEEDITIONWIDGET_H
#define UBTEACHERGUIDEEDITIONWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QDomElement>

#include "interfaces/IDataStorage.h"
#include "UBTGGlobals.h"
#include "UBTGAdaptableText.h"
#include "UBAddItem.h"
#include "UBTGModel.h"

typedef enum {
    eUBTGAddSubItemWidgetType_None,
    eUBTGAddSubItemWidgetType_Action,
    eUBTGAddSubItemWidgetType_Media,
    eUBTGAddSubItemWidgetType_Url
} eUBTGAddSubItemWidgetType;

class UBTeacherGuideEditionWidget : public QWidget , public IDataStorage
{
    Q_OBJECT
public:
    explicit UBTeacherGuideEditionWidget(UBTGModel* pModel, QWidget* parent = 0, const char* name="UBTeacherGuideEditionWidget");
    ~UBTeacherGuideEditionWidget();
    void cleanData();
    QVector<tUBGEElementNode*> getData();

    void load(QString element);
    QVector<tIDataStorage*> save(int pageIndex);

    bool isModified();

public slots:
    void onAddItemClicked(QTreeWidgetItem* widget, int column, QDomElement* element = 0);
    void onActiveSceneChanged();
    void showEvent(QShowEvent* event);

private:
    QList<QTreeWidgetItem*> getChildrenList(QTreeWidgetItem* widgetItem);
    QVector<tUBGEElementNode*> getPageAndCommentData();

    QVBoxLayout* mpLayout;
    QLabel* mpDocumentTitle;
    QLabel* mpPageNumberLabel;
    UBTGAdaptableText* mpPageTitle;
    UBTGAdaptableText* mpComment;
    QFrame* mpSeparator;
    QTreeWidget* mpTreeWidget;
    QTreeWidgetItem* mpRootWidgetItem;
    UBAddItem* mpAddAnActionItem;
    UBAddItem* mpAddAMediaItem;
    UBAddItem* mpAddALinkItem;
    UBTGModel* mpModel;

private slots:
    void onActiveDocumentChanged();
#ifdef Q_WS_MACX
    void onSliderMoved(int size);
#endif
};

#endif // UBTEACHERGUIDEEDITIONWIDGET_H
