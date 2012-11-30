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
#ifndef UBTEACHERGUIDEPRESENTATIONWIDGET_H
#define UBTEACHERGUIDEPRESENTATIONWIDGET_H
#include <QWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "UBTGGlobals.h"
#include "UBTGAdaptableText.h"
#include "UBTGDraggableTreeItem.h"
#include "UBTGModel.h"

typedef enum {
    tUBTGActionAssociateOnClickItem_NONE,
    tUBTGActionAssociateOnClickItem_URL,
    tUBTGActionAssociateOnClickItem_MEDIA,
    tUBTGActionAssociateOnClickItem_EXPAND
} tUBTGActionAssociateOnClickItem;

typedef enum {
    tUBTGTreeWidgetItemRole_HasAnAction = Qt::UserRole,
    tUBTGTreeWidgetItemRole_HasAnUrl
} tUBTGTreeWidgetItemRole;

class UBTeacherGuidePresentationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UBTeacherGuidePresentationWidget(UBTGModel* pModel, QWidget* parent, const char* name = "UBTeacherGuidePresentationName");
    ~UBTeacherGuidePresentationWidget();
    void showData(QVector<tUBGEElementNode*>data);
    void cleanData();

public slots:
    void onAddItemClicked(QTreeWidgetItem* widget, int column);
    void onActiveSceneChanged();

private:
    bool eventFilter(QObject* object, QEvent* event);

    void createMediaButtonItem();

    UBTGAdaptableText* mpPageTitle;
    UBTGAdaptableText* mpComment;
    QVBoxLayout* mpLayout;
    QHBoxLayout* mpButtonTitleLayout;
    QLabel* mpDocumentTitle;
    QLabel* mpPageNumberLabel;
    QFrame* mpSeparator;
    QPushButton* mpModePushButton;
    UBTGDraggableTreeItem* mpTreeWidget;
    QTreeWidgetItem* mpRootWidgetItem;
    QTreeWidgetItem* mpMediaSwitchItem;
    UBTGModel* mpModel;

#ifdef Q_WS_MACX
private slots:
    void onSliderMoved(int size);
#endif

};

#endif // UBTEACHERGUIDEPRESENTATIONWIDGET_H
