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
#ifndef UBTEACHERGUIDEPAGEZEROWIDGET_H
#define UBTEACHERGUIDEPAGEZEROWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QComboBox>

#include "abstract/UBAbstractMetaDataProvider.h"
#include "UBTGGlobals.h"
#include "UBTGAdaptableText.h"
#include "UBTGModel.h"


class UBTeacherGuidePageZeroWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UBTeacherGuidePageZeroWidget(UBTGModel* pModel, QWidget* parent, const char* name = "UBTeacherGuidePageZeroEditionWidget");
    ~UBTeacherGuidePageZeroWidget();

    QVector<tUBGEElementNode*> getData();
    bool isModified();

signals:
    void resized();

public slots:
    void onActiveSceneChanged();
    void switchToMode(tUBTGZeroPageMode mode = tUBTGZeroPageMode_EDITION);

protected:
    void resizeEvent(QResizeEvent* ev);

private:
    void fillComboBoxes();
    void loadData();
    void hideEvent(QHideEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
    void updateSceneTitle();

    QVBoxLayout* mpLayout;
    QHBoxLayout* mpButtonTitleLayout;
    QVBoxLayout* mpContainerWidgetLayout;
    QPushButton* mpModePushButton;
    QLabel* mpPageNumberLabel;

    QScrollArea* mpScrollArea;
    QWidget* mpContainerWidget;

    UBTGAdaptableText* mpSessionTitle;
    QFrame* mpSeparatorSessionTitle;

    QLabel* mpAuthorsLabel;
    UBTGAdaptableText* mpAuthors;
    QFrame* mpSeparatorAuthors;

    QLabel* mpCreationLabel;
    QLabel* mpLastModifiedLabel;
    QLabel* mpObjectivesLabel;
    UBTGAdaptableText* mpObjectives;
    QFrame* mpSeparatorObjectives;

    QLabel* mpIndexLabel;
    QLabel* mpKeywordsLabel;
    UBTGAdaptableText* mpKeywords;

    QLabel* mpSchoolLevelItemLabel;
    QComboBox* mpSchoolLevelBox;
    QLabel* mpSchoolLevelValueLabel;

    QLabel* mpSchoolSubjectsItemLabel;
    QComboBox* mpSchoolSubjectsBox;
    QLabel* mpSchoolSubjectsValueLabel;

    QLabel* mpSchoolTypeItemLabel;
    QComboBox* mpSchoolTypeBox;
    QLabel* mpSchoolTypeValueLabel;
    QFrame* mpSeparatorIndex;

    QLabel* mpLicenceLabel;
    QComboBox* mpLicenceBox;
    QLabel* mpLicenceValueLabel;
    QLabel* mpLicenceIcon;
    QHBoxLayout* mpLicenceLayout;

    //UBGraphicsTextItem* mpSceneItemSessionTitle;

    QMap<QString,QString> mGradeLevelsMap;
    QMap<QString,QStringList> mSubjects;

    UBTGModel* mpModel;

private slots:
    void onSchoolLevelChanged(QString schoolLevel);
    void persistData();
};

#endif // UBTEACHERGUIDEPAGEZEROWIDGET_H
