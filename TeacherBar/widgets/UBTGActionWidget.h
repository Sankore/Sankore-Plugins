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
#ifndef UBTGACTIONWIDGET_H
#define UBTGACTIONWIDGET_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QDomElement>
#include <QVBoxLayout>
#include <QComboBox>
#include <QTreeWidgetItem>

#include "UBTGAdaptableText.h"
#include "UBTGGlobals.h"

class UBTGActionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UBTGActionWidget(QTreeWidgetItem* widget, QWidget* parent = 0,const char* name = "UBTGActionWidget");
    ~UBTGActionWidget();
    void update();
    tUBGEElementNode* saveData();
    void initializeWithDom(QDomElement element);

private:
    QVBoxLayout* mpLayout;
    QComboBox* mpOwner;
    UBTGAdaptableText* mpTask;

protected:
    QTreeWidgetItem* mpTreeWidgetItem;
};

#endif // UBTGACTIONWIDGET_H
