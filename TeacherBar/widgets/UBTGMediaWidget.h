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
#ifndef UBTGMEDIAWIDGET_H
#define UBTGMEDIAWIDGET_H

#include <QStackedWidget>
#include <QTreeWidgetItem>
#include <QDomElement>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "UBTGGlobals.h"
#include "UBTGAdaptableText.h"
#include "UBTGMediaWidget.h"
#include "customWidgets/UBMediaWidget.h"
#include "UBTGDraggableWeb.h"

class UBTGMediaWidget : public QStackedWidget
{
    Q_OBJECT
public:
    UBTGMediaWidget(QTreeWidgetItem* widget = 0, QWidget* parent = 0, const char* name = "UBTGMediaWidget");
    UBTGMediaWidget(QString mediaFolder, QString mediaPath, QTreeWidgetItem* widget = 0, QWidget* parent = 0, bool forceFlashMediaType = false, const char *name = "UBTGMediaWidget");
    ~UBTGMediaWidget();
    tUBGEElementNode* saveData();
    void initializeWithDom(QDomElement element);
    void removeSource();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dropEvent(QDropEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void hideEvent(QHideEvent* event);
    void showEvent(QShowEvent* event);

private:
    void parseMimeData(const QMimeData* pMimeData);
    void createWorkWidget(bool forceFlashMediaType = false);
    void updateSize();

    QTreeWidgetItem* mpTreeWidgetItem;
    QLabel* mpDropMeWidget;
    QWidget* mpWorkWidget;
    QVBoxLayout* mpLayout;
    QHBoxLayout* mpMediaLayout;
    UBTGAdaptableText* mpTitle;
    QLabel* mpMediaLabelWidget;
    UBMediaWidget* mpMediaWidget;
    UBDraggableWeb* mpWebView;
    QString mMediaPath;
    QString mMediaFolder;
    bool mIsPresentationMode;
    QString mMediaType;
    bool mIsInitializationMode;
    int mMediaWidgetHeight;
};

#endif // UBTGMEDIAWIDGET_H
