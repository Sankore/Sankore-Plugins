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
#include <QApplication>
#include "UBAddItem.h"

UBAddItem::UBAddItem(const QString &string, int addSubItemWidgetType, QTreeWidget* parent): QTreeWidgetItem(parent)
{
    setIcon(0,QIcon(":images/increase.svg"));
    setText(0,string);
    setData(0,Qt::UserRole,QVariant(addSubItemWidgetType));
    setData(1,Qt::UserRole,QVariant(addSubItemWidgetType));
    setData(0,Qt::BackgroundRole,QVariant(QColor(200,200,200)));
    setData(1,Qt::BackgroundRole,QVariant(QColor(200,200,200)));
    setData(0,Qt::FontRole,QVariant(QFont(QApplication::font().family(),12)));
}

UBAddItem::~UBAddItem()
{
    //NOOP
}
