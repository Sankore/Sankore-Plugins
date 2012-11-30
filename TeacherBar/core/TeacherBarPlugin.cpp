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
#include <QtGui> // Needed to compile with Q_EXPORT_PLUGIN2 !
#include "TeacherBarPlugin.h"

TeacherBarPlugin::TeacherBarPlugin(){
    mpDockWidget = NULL;
    mpModel = new UBTGModel();
}

/**
 * \brief Get the dockable widget
 * @returns the dockable widget
 */
UBDockPaletteWidget *TeacherBarPlugin::dockableWidget(){
    if(NULL == mpDockWidget){
        mpDockWidget = new UBTGDockWidget(mpModel);
    }
    return mpDockWidget;
}

/**
 * \brief Set the current document
 * @param doc as the current document
 */
void TeacherBarPlugin::setDocument(IDocument *doc){
    mpDockWidget->setDocument(doc);
}

/**
 * \brief Get the current document
 * @returns the current document
 */
IDocument* TeacherBarPlugin::document(){
    return mpDockWidget->document();
}

/**
 * \brief Get the board user pointer
 * @returns the board user pointer
 */
QObject* TeacherBarPlugin::boardUser(){
    return this;
}

/**
 * \brief Slot used to react on the activeSceneChanged signal
 */
void TeacherBarPlugin::onActiveSceneChanged(){
    // TODO: Implement me!
}

/**
 * \brief Slot used to react on the documentSet signal
 */
void TeacherBarPlugin::onActiveDocumentChanged(){
    // TODO: Implement me!
}

/**
 * \brief Save the metadatas and add the namespace
 * @param ns as the namespace list where to put this class namespaces
 * @param md as the metadata list where to put this class metadatas
 */
void TeacherBarPlugin::save(QList<sNamespace> &ns, QList<sMetaData> &md){
    mpModel->save(ns, md);
}

/**
 * \brief Get the namespace
 * @return the namespace
 */
QString TeacherBarPlugin::nameSpace(){
    return mpModel->nameSpace();
}

/**
 * \brief Get the namespace url
 * @return the namespace url
 */
QString TeacherBarPlugin::nameSpaceUrl(){
    return mpModel->nameSpaceUrl();
}


void TeacherBarPlugin::updateModel(){
    if(NULL != mpDockWidget && NULL != mpDockWidget->document()){
        // TODO: Implement me!
    }
}

Q_EXPORT_PLUGIN2(TeacherBar, TeacherBarPlugin)
