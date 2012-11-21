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
#ifndef UBTGDOCKWIDGET_H
#define UBTGDOCKWIDGET_H

#include "customWidgets/UBDockPaletteWidget.h"
#include "interfaces/IDocumentUser.h"
#include "interfaces/IDocument.h"

class UBTGDockWidget : public UBDockPaletteWidget, public IDocumentUser{
    //Q_OBJECT
    Q_INTERFACES(IDocumentUser)

public:
    UBTGDockWidget(QWidget* parent=0, const char* name="UBTGDockWidget");
    ~UBTGDockWidget();
    virtual bool visibleInMode(eUBDockPaletteWidgetMode mode);
    void setDocument(IDocument *doc);
    IDocument* document();

private:
    IDocument* mpDocument;
};

#endif // UBTGDOCKWIDGET_H
