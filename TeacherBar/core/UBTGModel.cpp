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
#include "UBTGModel.h"

const QString qsNamespace = "ub";
const QString qsNamespaceUrl = "http://uniboard.mnemis.com/document";

const QString qsMetaTitle = "";
const QString qsMetaAuthor = "";
const QString qsMetaObjectives = "";
const QString qsMetaKeywords = "";
const QString qsMetaGradeLevel = "";
const QString qsMetaSubjects = "";
const QString qsMetaType = "";
const QString qsMetaLicense = "";

/**
 * \brief Constructor
 */
UBTGModel::UBTGModel(){

}

/**
 * \brief Destructor
 */
UBTGModel::~UBTGModel(){

}

/**
 * \brief Save the metadatas and add the namespace
 * @param ns as the namespace list where to put this class namespaces
 * @param md as the metadata list where to put this class metadatas
 */
void UBTGModel::save(QList<sNamespace> &ns, QList<sMetaData> &md){
    QVector<sMetaData>::const_iterator itMetaData;
    for(itMetaData = mMetaDatas.constBegin(); itMetaData != mMetaDatas.constEnd(); itMetaData++){
        sMetaData meta;
        meta.key = itMetaData->key;
        meta.ns = itMetaData->ns;
        meta.value = itMetaData->value;
        md.append(meta);
    }

    sNamespace ubNs;
    ubNs.name = qsNamespace;
    ubNs.url = qsNamespaceUrl;

    ns.append(ubNs);
}

/**
 * \brief Get the namespace
 * @return the namespace
 */
QString UBTGModel::nameSpace(){
    return qsNamespace;
}

/**
 * \brief Get the namespace url
 * @return the namespace url
 */
QString UBTGModel::nameSpaceUrl(){
    return qsNamespaceUrl;
}
