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
#include "UBTGAdaptableText.h"

UBTGAdaptableText::UBTGAdaptableText(QTreeWidgetItem* widget, QWidget* parent, const char* name):QTextEdit(parent)
  , mBottomMargin(5)
  , mpTreeWidgetItem(widget)
  , mMinimumHeight(0)
  , mHasPlaceHolder(false)
  , mIsUpdatingSize(false)
  , mMaximumLength(0)
{
    setObjectName(name);
    connect(this,SIGNAL(textChanged()),this,SLOT(onTextChanged()));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mMinimumHeight = document()->size().height() + mBottomMargin;
    setMinimumHeight(mMinimumHeight);

}

void UBTGAdaptableText::setMaximumLength(int length)
{
    mMaximumLength = length;
}

void UBTGAdaptableText::setPlaceHolderText(QString text)
{
    mHasPlaceHolder = true;

    // the space addition is to make this string unique and check against it to know
    // if we are talking about a typed string or the placeholder string
    mPlaceHolderText = text + "     ";
    setPlainText(mPlaceHolderText);
}

void UBTGAdaptableText::keyReleaseEvent(QKeyEvent* e)
{
    QTextEdit::keyReleaseEvent(e);

    if(mMaximumLength && toPlainText().length()>mMaximumLength){
        setPlainText(toPlainText().left(mMaximumLength));
        QTextCursor tc(document());
        tc.setPosition(mMaximumLength);
        setTextCursor(tc);
    }
}

void UBTGAdaptableText::showEvent(QShowEvent* e)
{
    Q_UNUSED(e);
    if(!mIsUpdatingSize && !hasFocus() && mHasPlaceHolder && toPlainText().isEmpty() && !isReadOnly()){
        setTextColor(QColor(Qt::lightGray));
        setPlainText(mPlaceHolderText);
    }
    else
        // If the teacherguide is collapsed, don't updated the size. Or set the size as the expanded size
        onTextChanged();
}

QString UBTGAdaptableText::text()
{
    QString result = toPlainText();
    if(mHasPlaceHolder && result == mPlaceHolderText)
        return "";

    return result;
}

void UBTGAdaptableText::onTextChanged()
{
    qreal documentSize = document()->size().height();
    if(height() == documentSize + mBottomMargin){
        return;
    }
    mIsUpdatingSize = true;


    if(documentSize < mMinimumHeight){
        setFixedHeight(mMinimumHeight);
    }
    else{
        setFixedHeight(documentSize+mBottomMargin);
    }

    updateGeometry();
    //to trig a resize on the tree widget item
    if(mpTreeWidgetItem){
        mpTreeWidgetItem->setDisabled(true);
        mpTreeWidgetItem->setExpanded(true);
        mpTreeWidgetItem->setDisabled(false);
        setFocus();
    }
    mIsUpdatingSize = false;
}

void UBTGAdaptableText::setInitialText(const QString& text)
{
    setText(text);
    setReadOnly(false);
    onTextChanged();
}

void UBTGAdaptableText::showText(const QString & text)
{
    setText(text);
    setReadOnly(true);
    onTextChanged();
}

void UBTGAdaptableText::bottomMargin(int newValue)
{
    mBottomMargin = newValue;
    onTextChanged();
}

void UBTGAdaptableText::focusInEvent(QFocusEvent* e)
{
    if(isReadOnly()){
        e->ignore();
    }
    managePlaceholder(true);
    QTextEdit::focusInEvent(e);
}

void UBTGAdaptableText::focusOutEvent(QFocusEvent* e)
{
    managePlaceholder(false);
    QTextEdit::focusOutEvent(e);
}

void UBTGAdaptableText::managePlaceholder(bool focus)
{
    if(focus){
        if(toPlainText() == mPlaceHolderText){
            setTextColor(QColor(Qt::black));
            setPlainText("");
        }
        setCursorToTheEnd();
    }
    else{
        if(toPlainText().isEmpty()){
            setTextColor(QColor(Qt::lightGray));
            setPlainText(mPlaceHolderText);
        }
    }
}

void UBTGAdaptableText::setCursorToTheEnd()
{
    QTextDocument* doc = document();
    if(NULL != doc){
        QTextBlock block = doc->lastBlock();
        QTextCursor cursor(doc);
        cursor.setPosition(block.position() + block.length() - 1);
        setTextCursor(cursor);
    }
}
