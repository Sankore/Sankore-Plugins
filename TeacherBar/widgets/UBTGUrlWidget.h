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
#ifndef UBTGURLWIDGET_H
#define UBTGURLWIDGET_H

#include <QDomElement>
#include <QVBoxLayout>
#include <QLineEdit>
#include "UBTGGlobals.h"

class UBTGUrlWidget : public QWidget
{
    Q_OBJECT
public:
    UBTGUrlWidget(QWidget* parent = 0, const char* name = "UBTGUrlWidget");
    ~UBTGUrlWidget();
    tUBGEElementNode* saveData();
    void initializeWithDom(QDomElement element);

public slots:
    void onUrlEditionFinished();

private:
    QVBoxLayout* mpLayout;
    QLineEdit* mpTitle;
    QLineEdit* mpUrl;
};

#endif // UBTGURLWIDGET_H
