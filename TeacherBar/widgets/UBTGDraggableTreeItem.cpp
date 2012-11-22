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
#include <QUrl>

#include "UBTGDraggableTreeItem.h"

UBTGDraggableTreeItem::UBTGDraggableTreeItem(QWidget* parent, const char* name) : QTreeWidget(parent)
{
    setObjectName(name);
}

QMimeData* UBTGDraggableTreeItem::mimeData(const QList<QTreeWidgetItem *> items) const
{
    QMimeData* result = new QMimeData();
    QList<QUrl> urls;
    urls << QUrl(items.at(0)->data(0,TG_USER_ROLE_MIME_TYPE).toString());
    result->setUrls(urls);
    return result;
}
