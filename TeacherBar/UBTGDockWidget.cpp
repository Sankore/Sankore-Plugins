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
#include "UBTGDockWidget.h"

/**
 * \brief Constructor
 * @param parent as the parent widget
 * @param name as the object name
 */
UBTGDockWidget::UBTGDockWidget(QWidget *parent, const char *name):UBDockPaletteWidget(parent, name)
  , mpDocument(NULL)
{

}

/**
 * \brief Destructor
 */
UBTGDockWidget::~UBTGDockWidget(){

}

/**
 * \brief Get the visible mode
 * @returns a boolean telling the visible state
 */
bool UBTGDockWidget::visibleInMode(eUBDockPaletteWidgetMode mode){
    return mode == eUBDockPaletteWidget_BOARD;
}

/**
 * \brief Set the current document
 * @param doc as the current document
 */
void UBTGDockWidget::setDocument(IDocument *doc){
    mpDocument = doc;
}

/**
 * \brief Get the current document
 * @returns a pointer on the current document
 */
IDocument* UBTGDockWidget::document(){
    return mpDocument;
}
