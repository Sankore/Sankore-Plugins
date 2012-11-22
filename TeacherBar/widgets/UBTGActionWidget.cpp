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
#include "globals/UBGlobals.h"
#include "UBTGActionWidget.h"

UBTGActionWidget::UBTGActionWidget(QTreeWidgetItem* widget, QWidget* parent, const char* name) : QWidget(parent)
  , mpLayout(NULL)
  , mpOwner(NULL)
  , mpTask(NULL)
{
    setObjectName(name);
    SET_STYLE_SHEET();
    mpLayout = new QVBoxLayout(this);
    mpOwner = new QComboBox(this);
    mpOwner->setObjectName("DockPaletteWidgetComboBox");
    mpOwner->setMinimumHeight(22);
    QStringList qslOwner;
    qslOwner << tr("Teacher") << tr("Student");
    mpOwner->insertItems(0,qslOwner);
    mpOwner->setCurrentIndex(0);
    mpTask = new UBTGAdaptableText(widget,this);
    mpTask->setPlaceHolderText(tr("Type task here ..."));
    mpTask->setAcceptRichText(true);
    mpTask->setObjectName("ActionWidgetTaskTextEdit");
    mpLayout->addWidget(mpOwner);
    mpLayout->addWidget(mpTask);
}

UBTGActionWidget::~UBTGActionWidget()
{
    DELETEPTR(mpOwner);
    DELETEPTR(mpTask);
    DELETEPTR(mpLayout);
}

void UBTGActionWidget::initializeWithDom(QDomElement element)
{
    mpOwner->setCurrentIndex(element.attribute("owner").toInt());
    mpTask->setInitialText(element.attribute("task"));
}

tUBGEElementNode* UBTGActionWidget::saveData()
{
    tUBGEElementNode* result = new tUBGEElementNode();
    result->name = "action";
    result->attributes.insert("owner",QString("%0").arg(mpOwner->currentIndex()));
    result->attributes.insert("task",mpTask->text());
    return result;
}
