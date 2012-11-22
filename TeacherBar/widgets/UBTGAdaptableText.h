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
#ifndef UBTGADAPTABLETEXT_H
#define UBTGADAPTABLETEXT_H

#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QFocusEvent>
#include <QTextBlock>

class UBTGAdaptableText : public QTextEdit
{
    Q_OBJECT
public:
    explicit UBTGAdaptableText(QTreeWidgetItem* widget = 0, QWidget *parent = 0, const char* name = "UBTGAdaptableText");
    void showText(const QString & text);
    void bottomMargin(int newValue);
    void setPlaceHolderText(QString text);
    QString text();
    void setInitialText(const QString& text);
    void setMaximumLength(int length);
    void managePlaceholder(bool focus);

public slots:
    void onTextChanged();

protected:
    void keyReleaseEvent(QKeyEvent* e);
    void showEvent(QShowEvent* e);
    void focusInEvent(QFocusEvent* e);
    void focusOutEvent(QFocusEvent* e);

private:
    void setCursorToTheEnd();
    int mBottomMargin;
    QTreeWidgetItem* mpTreeWidgetItem;
    int mMinimumHeight;
    bool mHasPlaceHolder;
    QString mPlaceHolderText;
    bool mIsUpdatingSize;
    int mMaximumLength;
};

#endif // UBTGADAPTABLETEXT_H
