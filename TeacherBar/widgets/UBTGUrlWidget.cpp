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
#include "UBTGUrlWidget.h"
#include "globals/UBGlobals.h"

UBTGUrlWidget::UBTGUrlWidget(QWidget* parent, const char* name ):QWidget(parent)
  , mpLayout(NULL)
  , mpTitle(NULL)
  , mpUrl(NULL)
{
    setObjectName(name);
    SET_STYLE_SHEET();
    mpLayout = new QVBoxLayout(this);
    setLayout(mpLayout);
    mpTitle = new QLineEdit(this);
    mpTitle->setObjectName("UBTGLineEdit");
    mpTitle->setPlaceholderText(tr("Insert link title here..."));
    mpUrl = new QLineEdit(this);
    connect(mpUrl,SIGNAL(editingFinished()),this,SLOT(onUrlEditionFinished()));
    mpUrl->setObjectName("UBTGLineEdit");
    mpUrl->setPlaceholderText("http://");
    mpLayout->addWidget(mpTitle);
    mpLayout->addWidget(mpUrl);
}

UBTGUrlWidget::~UBTGUrlWidget()
{
    DELETEPTR(mpTitle);
    DELETEPTR(mpUrl);
    DELETEPTR(mpLayout);
}

void UBTGUrlWidget::onUrlEditionFinished()
{
    QString url = mpUrl->text();
    if(url.length() && !url.startsWith("http://") && !url.startsWith("https://") && !url.startsWith("ftp://") && !url.startsWith("sftp://") && !url.startsWith("http://")){
        mpUrl->setText("http://" + mpUrl->text());
        setFocus();
    }
}

void UBTGUrlWidget::initializeWithDom(QDomElement element)
{
    mpTitle->setText(element.attribute("title"));
    mpUrl->setText(element.attribute("url"));
}

tUBGEElementNode* UBTGUrlWidget::saveData()
{
    tUBGEElementNode* result = new tUBGEElementNode();
    result->name = "link";
    result->attributes.insert("title",mpTitle->text());
    result->attributes.insert("url",mpUrl->text());
    return result;
}
