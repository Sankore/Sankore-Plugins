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
#ifndef UBTGMODEL_H
#define UBTGMODEL_H

#include "abstract/UBAbstractMetaDataProvider.h"

class UBTGModel : public UBAbstractMetaDataProvider{
public:
    UBTGModel();
    virtual ~UBTGModel();

    virtual void save(QList<sNamespace> &ns, QList<sMetaData> &md);
    virtual QString nameSpace();
    virtual QString nameSpaceUrl();
};

#endif // UBTGMODEL_H
