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
#include "UBTGDraggableWeb.h"

UBDraggableWeb::UBDraggableWeb(QString& relativePath, QWidget* parent): QWebView(parent)
  , mDragStartPosition(QPoint(-1,-1))
  , mDragStarted(false)

{
    if(!relativePath.startsWith("file://"))
        mRelativePath = QUrl::fromLocalFile(relativePath).toString();
    else
        mRelativePath = relativePath;
    //NOOP
}

void UBDraggableWeb::mousePressEvent(QMouseEvent* event)
{
    mDragStartPosition = event->pos();
    mDragStarted = true;
    QWebView::mousePressEvent(event);
}

void UBDraggableWeb::mouseReleaseEvent(QMouseEvent* event)
{
    mDragStarted = false;
    QWebView::mouseReleaseEvent(event);
}

void UBDraggableWeb::mouseMoveEvent(QMouseEvent* event)
{
    if(mDragStarted && (event->pos() - mDragStartPosition).manhattanLength() > QApplication::startDragDistance()){
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        QList<QUrl> urlList;
        urlList << QUrl(mRelativePath);
        mimeData->setUrls(urlList);
        drag->setMimeData(mimeData);

        drag->exec();
        event->accept();
        mDragStarted = false;
    }
    else
        QWebView::mouseMoveEvent(event);

}
