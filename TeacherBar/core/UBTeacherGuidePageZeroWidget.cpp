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
#include <QApplication>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>

#include "UBTeacherGuidePageZeroWidget.h"
#include "globals/UBGlobals.h"

UBTeacherGuidePageZeroWidget::UBTeacherGuidePageZeroWidget(UBTGModel* pModel, QWidget* parent, const char* name) :
    QWidget(parent)
  , mpLayout(NULL)
  , mpButtonTitleLayout(NULL)
  , mpContainerWidgetLayout(NULL)
  , mpModePushButton(NULL)
  , mpPageNumberLabel(NULL)
  , mpScrollArea(NULL)
  , mpContainerWidget(NULL)
  , mpSessionTitle(NULL)
  , mpSeparatorSessionTitle(NULL)
  , mpAuthorsLabel(NULL)
  , mpAuthors(NULL)
  , mpSeparatorAuthors(NULL)
  , mpCreationLabel(NULL)
  , mpLastModifiedLabel(NULL)
  , mpObjectivesLabel(NULL)
  , mpObjectives(NULL)
  , mpSeparatorObjectives(NULL)
  , mpIndexLabel(NULL)
  , mpKeywordsLabel(NULL)
  , mpKeywords(NULL)
  , mpSchoolLevelItemLabel(NULL)
  , mpSchoolLevelBox(NULL)
  , mpSchoolLevelValueLabel(NULL)
  , mpSchoolSubjectsItemLabel(NULL)
  , mpSchoolSubjectsBox(NULL)
  , mpSchoolSubjectsValueLabel(NULL)
  , mpSchoolTypeItemLabel(NULL)
  , mpSchoolTypeBox(NULL)
  , mpSchoolTypeValueLabel(NULL)
  , mpSeparatorIndex(NULL)
  , mpLicenceLabel(NULL)
  , mpLicenceBox( NULL)
  , mpLicenceIcon(NULL)
  , mpLicenceLayout(NULL)
  , mpModel(pModel)
  //, mpSceneItemSessionTitle(NULL)
{
    QWidget::setObjectName(name);
    QString chapterStyle("QLabel {font-size:16px; font-weight:bold;}");
    mpLayout = new QVBoxLayout(0);
    setLayout(mpLayout);
    mpPageNumberLabel = new QLabel(this);
    mpPageNumberLabel->setAlignment(Qt::AlignRight);
    mpPageNumberLabel->setObjectName("UBTGPageNumberLabel");
    mpPageNumberLabel->setText(tr("Title page"));
    mpLayout->addWidget(mpPageNumberLabel);

    mpScrollArea = new QScrollArea();
    mpScrollArea->setFocusPolicy(Qt::NoFocus);
    mpContainerWidget = new QWidget();
    mpContainerWidget->setFocusPolicy(Qt::NoFocus);
    mpContainerWidgetLayout = new QVBoxLayout();

    mpLayout->addWidget(mpScrollArea);
    mpScrollArea->setWidget(mpContainerWidget);
    mpScrollArea->setWidgetResizable(true);
    mpScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpContainerWidget->setLayout(mpContainerWidgetLayout);

    mpButtonTitleLayout = new QHBoxLayout(0);

    mpModePushButton = new QPushButton(this);
    mpModePushButton->setIcon(QIcon(":images/teacherGuide/pencil.svg"));
    mpModePushButton->setMaximumWidth(32);
    mpModePushButton->installEventFilter(this);
    mpButtonTitleLayout->addWidget(mpModePushButton);
    connect(mpModePushButton, SIGNAL(clicked()), this, SLOT(switchToMode()));

    mpSessionTitle = new UBTGAdaptableText(0, this, "UBTGSessionTitle");
    mpSessionTitle->setPlaceHolderText(tr("Type session title here ..."));
    mpSessionTitle->setMaximumLength(1000);
    mpButtonTitleLayout->addWidget(mpSessionTitle);
    connect(this, SIGNAL(resized()), mpSessionTitle, SLOT(onTextChanged()));

    mpContainerWidgetLayout->addLayout(mpButtonTitleLayout);

    mpSeparatorSessionTitle = new QFrame(this);
    mpSeparatorSessionTitle->setFixedHeight(UBTG_SEPARATOR_FIXED_HEIGHT);
    mpSeparatorSessionTitle->setObjectName("UBTGSeparator");
    mpContainerWidgetLayout->addWidget(mpSeparatorSessionTitle);

    mpAuthorsLabel = new QLabel(this);
    mpAuthorsLabel->setObjectName("UBTGZeroPageEditionModeTitle");
    mpAuthorsLabel->setText(tr("Author(s)"));
    mpAuthorsLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpAuthorsLabel);

    mpAuthors = new UBTGAdaptableText(0, this);
    mpAuthors->setObjectName("UBTGZeroPageInputText");
    mpAuthors->setPlaceHolderText(tr("Type authors here ..."));
    mpContainerWidgetLayout->addWidget(mpAuthors);
    connect(this, SIGNAL(resized()), mpAuthors, SLOT(onTextChanged()));

    mpCreationLabel = new QLabel(this);
    mpCreationLabel->setObjectName("UBTGZeroPageDateLabel");
    mpCreationLabel->setText(tr("Creation date:"));
    mpContainerWidgetLayout->addWidget(mpCreationLabel);

    mpLastModifiedLabel = new QLabel(this);
    mpLastModifiedLabel->setObjectName("UBTGZeroPageDateLabel");
    mpLastModifiedLabel->setText(tr("Last Modified:"));
    mpContainerWidgetLayout->addWidget(mpLastModifiedLabel);

    mpSeparatorAuthors = new QFrame(this);
    mpSeparatorAuthors->setFixedHeight(UBTG_SEPARATOR_FIXED_HEIGHT);
    mpSeparatorAuthors->setObjectName("UBTGSeparator");
    mpContainerWidgetLayout->addWidget(mpSeparatorAuthors);

    mpObjectivesLabel = new QLabel(this);
    mpObjectivesLabel->setObjectName("UBTGZeroPageEditionModeTitle");
    mpObjectivesLabel->setText(tr("Objective(s)"));
    mpObjectivesLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpObjectivesLabel);

    mpObjectives = new UBTGAdaptableText(0, this);
    mpObjectives->setObjectName("UBTGZeroPageInputText");
    mpObjectives->setPlaceHolderText(tr("Type objectives here..."));
    mpContainerWidgetLayout->addWidget(mpObjectives);
    connect(this, SIGNAL(resized()), mpObjectives, SLOT(onTextChanged()));

    mpSeparatorObjectives = new QFrame(this);
    mpSeparatorObjectives->setFixedHeight(UBTG_SEPARATOR_FIXED_HEIGHT);
    mpSeparatorObjectives->setObjectName("UBTGSeparator");
    mpContainerWidgetLayout->addWidget(mpSeparatorObjectives);

    mpIndexLabel = new QLabel(this);
    mpIndexLabel->setObjectName("UBTGZeroPageEditionModeTitle");
    mpIndexLabel->setText(tr("Resource indexing"));
    mpIndexLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpIndexLabel);

    mpKeywordsLabel = new QLabel(this);
    mpKeywordsLabel->setObjectName("UBTGZeroPageItemLabel");
    mpKeywordsLabel->setText(tr("Keywords:"));
    mpKeywordsLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpKeywordsLabel);
    mpKeywords = new UBTGAdaptableText(0, this);
    mpKeywords->setPlaceHolderText(tr("Type keywords here ..."));
    mpContainerWidgetLayout->addWidget(mpKeywords);
    connect(this, SIGNAL(resized()), mpKeywords, SLOT(onTextChanged()));

    mpSchoolLevelItemLabel = new QLabel(this);
    mpSchoolLevelItemLabel->setObjectName("UBTGZeroPageItemLabel");
    mpSchoolLevelItemLabel->setText(tr("Level:"));
    mpSchoolLevelItemLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpSchoolLevelItemLabel);
    mpSchoolLevelBox = new QComboBox(this);
    mpSchoolLevelBox->setMinimumHeight(22);
    mpSchoolLevelBox->setMinimumWidth(LOWER_RESIZE_WIDTH);
    mpSchoolLevelBox->setObjectName("DockPaletteWidgetComboBox");
    connect(mpSchoolLevelBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(onSchoolLevelChanged(QString)));
    mpContainerWidgetLayout->addWidget(mpSchoolLevelBox);
    mpSchoolLevelValueLabel = new QLabel(this);
    mpContainerWidgetLayout->addWidget(mpSchoolLevelValueLabel);

    mpSchoolSubjectsItemLabel = new QLabel(this);
    mpSchoolSubjectsItemLabel->setObjectName("UBTGZeroPageItemLabel");
    mpSchoolSubjectsItemLabel->setText(tr("Subjects:"));
    mpSchoolSubjectsItemLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpSchoolSubjectsItemLabel);
    mpSchoolSubjectsBox = new QComboBox(this);
    mpSchoolSubjectsBox->setMinimumHeight(22);
    mpSchoolSubjectsBox->setMinimumWidth(LOWER_RESIZE_WIDTH);
    mpSchoolSubjectsBox->setObjectName("DockPaletteWidgetComboBox");
    mpContainerWidgetLayout->addWidget(mpSchoolSubjectsBox);
    mpSchoolSubjectsValueLabel = new QLabel(this);
    mpContainerWidgetLayout->addWidget(mpSchoolSubjectsValueLabel);

    mpSchoolTypeItemLabel = new QLabel(this);
    mpSchoolTypeItemLabel->setObjectName("UBTGZeroPageItemLabel");
    mpSchoolTypeItemLabel->setText(tr("Type:"));
    mpSchoolTypeItemLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpSchoolTypeItemLabel);
    mpSchoolTypeBox = new QComboBox(this);
    mpSchoolTypeBox->setMinimumHeight(22);
    mpSchoolTypeBox->setMinimumWidth(LOWER_RESIZE_WIDTH);
    mpSchoolTypeBox->setObjectName("DockPaletteWidgetComboBox");
    mpContainerWidgetLayout->addWidget(mpSchoolTypeBox);
    mpSchoolTypeValueLabel = new QLabel(this);
    mpContainerWidgetLayout->addWidget(mpSchoolTypeValueLabel);

    mpSeparatorIndex = new QFrame(this);
    mpSeparatorIndex->setFixedHeight(UBTG_SEPARATOR_FIXED_HEIGHT);
    mpSeparatorIndex->setObjectName("UBTGSeparator");
    mpContainerWidgetLayout->addWidget(mpSeparatorIndex);

    mpLicenceLabel = new QLabel(this);
    mpLicenceLabel->setObjectName("UBTGZeroPageItemLabel");
    mpLicenceLabel->setText(tr("Licence"));
    mpLicenceLabel->setStyleSheet(chapterStyle);
    mpContainerWidgetLayout->addWidget(mpLicenceLabel);
    mpLicenceBox = new QComboBox(this);
    mpLicenceBox->setMinimumHeight(22);
    mpLicenceBox->setMinimumWidth(LOWER_RESIZE_WIDTH);
    mpLicenceBox->setObjectName("DockPaletteWidgetComboBox");
    mpContainerWidgetLayout->addWidget(mpLicenceBox);
    mpLicenceLayout = new QHBoxLayout(0);
    mpLicenceIcon = new QLabel(this);
    mpLicenceIcon->setMinimumWidth(LOWER_RESIZE_WIDTH/2);
    mpLicenceLayout->addWidget(mpLicenceIcon);
    mpLicenceValueLabel = new QLabel(this);
    mpLicenceValueLabel->setMinimumWidth(LOWER_RESIZE_WIDTH/2);
    mpLicenceLayout->addWidget(mpLicenceValueLabel);
    mpContainerWidgetLayout->addLayout(mpLicenceLayout);
    mpContainerWidgetLayout->addStretch(1);

    //connect(UBApplication::boardController, SIGNAL(activeSceneChanged()), this, SLOT(onActiveSceneChanged()));
    fillComboBoxes();

    // Register the metadatas
//    addMetaData(nameSpace(), UBSettings::sessionTitle, mpSessionTitle->text());
//    addMetaData(nameSpace(), UBSettings::sessionAuthors, mpAuthors->text());
//    addMetaData(nameSpace(), UBSettings::sessionObjectives, mpObjectives->text());
//    addMetaData(nameSpace(), UBSettings::sessionKeywords, mpKeywords->text());
//    addMetaData(nameSpace(), UBSettings::sessionGradeLevel, mpSchoolLevelBox->currentText());
//    addMetaData(nameSpace(), UBSettings::sessionSubjects, mpSchoolSubjectsBox->currentText());
//    addMetaData(nameSpace(), UBSettings::sessionType, mpSchoolTypeBox->currentText());
//    addMetaData(nameSpace(), UBSettings::sessionLicence, QString("%0").arg(mpLicenceBox->currentIndex()));

//    UBApplication::documentController->currentDocument()->registerMetaDataProvider(this);
}

UBTeacherGuidePageZeroWidget::~UBTeacherGuidePageZeroWidget()
{
    DELETEPTR(mpPageNumberLabel);
    DELETEPTR(mpSessionTitle);
    DELETEPTR(mpSeparatorSessionTitle);
    DELETEPTR(mpAuthorsLabel);
    DELETEPTR(mpAuthors);
    DELETEPTR(mpSeparatorAuthors);
    DELETEPTR(mpCreationLabel);
    DELETEPTR(mpLastModifiedLabel);
    DELETEPTR(mpObjectivesLabel);
    DELETEPTR(mpObjectives);
    DELETEPTR(mpSeparatorObjectives);
    DELETEPTR(mpIndexLabel);
    DELETEPTR(mpKeywordsLabel);
    DELETEPTR(mpKeywords);
    DELETEPTR(mpSchoolLevelItemLabel);
    DELETEPTR(mpSchoolLevelBox);
    DELETEPTR(mpSchoolSubjectsItemLabel);
    DELETEPTR(mpSchoolSubjectsBox);
    DELETEPTR(mpSchoolTypeItemLabel);
    DELETEPTR(mpSchoolTypeBox);
    DELETEPTR(mpSeparatorIndex);
    DELETEPTR(mpLicenceLabel);
    DELETEPTR(mpLicenceBox);
    DELETEPTR(mpLicenceValueLabel);
    DELETEPTR(mpLicenceIcon);
    DELETEPTR(mpModePushButton);
    DELETEPTR(mpLicenceLayout);
    DELETEPTR(mpButtonTitleLayout);
    DELETEPTR(mpContainerWidgetLayout);
    DELETEPTR(mpContainerWidget);
    DELETEPTR(mpScrollArea);
    DELETEPTR(mpLayout);
}

bool UBTeacherGuidePageZeroWidget::eventFilter(QObject* object, QEvent* event)
{
    Q_UNUSED(object);
    if (event->type() == QEvent::HoverEnter || event->type() == QEvent::HoverMove || event->type() == QEvent::HoverLeave)
        return true;
    return false;
}

void UBTeacherGuidePageZeroWidget::fillComboBoxes()
{
    QFile parametersFile(":xml/indexingParameters.xml");
    if(!parametersFile.exists()){
        qCritical() << "Teacher Guide: cannot find the configuration file.";
        return;
    }

    if(parametersFile.open(QFile::ReadOnly)){
        QDomDocument doc;
        doc.setContent(parametersFile.readAll());
        QDomElement rootElement = doc.elementsByTagName("teacherGuide").at(0).toElement();

        QDomNodeList subjects = rootElement.elementsByTagName("subjects");
        for (int baseLevelCounter = 0; baseLevelCounter < subjects.count(); baseLevelCounter += 1) {
            QDomNode subjectsForBaseLevel = subjects.at(baseLevelCounter);
            QDomNodeList subjectsList = subjectsForBaseLevel.childNodes();
            QStringList subjectsRelatedToBaseLevel;
            for (int j = 0; j < subjectsList.count(); j += 1) {
                subjectsRelatedToBaseLevel.append(subjectsList.at(j).toElement().attribute("label"));
            }
            mSubjects.insert( subjectsForBaseLevel.toElement().attribute("baseLevel"), subjectsRelatedToBaseLevel);
        }

        QDomNodeList gradeLevels = rootElement.elementsByTagName("gradeLevels").at(0).childNodes();
        for (int i = 0; i < gradeLevels.count(); i += 1) {
            mGradeLevelsMap.insert(gradeLevels.at(i).toElement().attribute("label"), gradeLevels.at(i).toElement().attribute("baseLevel"));
            mpSchoolLevelBox->addItem( gradeLevels.at(i).toElement().attribute("label"));
        }

        QDomNodeList types = rootElement.elementsByTagName("types").at(0).childNodes();
        for (int i = 0; i < types.count(); i += 1)
            mpSchoolTypeBox->addItem(types.at(i).toElement().attribute("label"));

        parametersFile.close();

        QStringList licences;
        licences << tr("Attribution-ShareAlike CC BY-SA")
                 << tr("Attribution CC BY")
                 << tr("Attribution-NoDerivs CC BY-ND")
                 << tr("Attribution-NonCommercial CC BY-NC")
                 << tr("Attribution-NonCommercial-NoDerivs CC BY-NC-ND")
                 << tr("Attribution-NonCommercial-ShareAlike CC BY-NC-SA")
                 << tr("Public domain")
                 << tr("Copyright");
        mpLicenceBox->addItems(licences);
        QStringList licenceIconList;
        licenceIconList << ":images/licenses/ccbysa.png"
                        << ":images/licenses/ccby.png"
                        << ":images/licenses/ccbynd.png"
                        << ":images/licenses/ccbync.png"
                        << ":images/licenses/ccbyncnd.png"
                        << ":images/licenses/ccbyncsa.png";
        for (int i = 0; i < licenceIconList.count(); i += 1)
            mpLicenceBox->setItemData(i, licenceIconList.at(i));
    }else{
        qCritical() << "Teacher Guide: cannot open the configuration file.";
    }
}

void UBTeacherGuidePageZeroWidget::onSchoolLevelChanged(QString schoolLevel)
{
    QStringList subjects = mSubjects.value(mGradeLevelsMap.value(schoolLevel));
    mpSchoolSubjectsBox->clear();
    if (subjects.count()) {
        mpSchoolSubjectsItemLabel->setEnabled(true);
        mpSchoolSubjectsBox->setEnabled(true);
        mpSchoolSubjectsBox->addItems(subjects);
    }
    else {
        mpSchoolSubjectsItemLabel->setDisabled(true);
        mpSchoolSubjectsBox->setDisabled(true);
    }
}

void UBTeacherGuidePageZeroWidget::onActiveSceneChanged()
{
//    UBDocumentProxy* documentProxy = UBApplication::boardController->selectedDocument();
//    if (documentProxy && UBApplication::boardController->currentPage() == 0) {
//        QDateTime creationDate = documentProxy->documentDate();
//        mpCreationLabel->setText( tr("Created the:\n") + creationDate.toString(Qt::DefaultLocaleShortDate));
//        QDateTime updatedDate = documentProxy->lastUpdate();
//        mpLastModifiedLabel->setText( tr("Updated the:\n") + updatedDate.toString(Qt::DefaultLocaleShortDate));
//        loadData();
//        updateSceneTitle();
//    }
}

void UBTeacherGuidePageZeroWidget::hideEvent(QHideEvent * event)
{
    persistData();
    QWidget::hideEvent(event);
}

void UBTeacherGuidePageZeroWidget::loadData()
{
//    UBDocumentProxy* documentProxy = UBApplication::boardController->selectedDocument();
//    mpSessionTitle->setText( documentProxy->metaData(UBSettings::sessionTitle).toString());
//    mpAuthors->setText( documentProxy->metaData(UBSettings::sessionAuthors).toString());
//    mpObjectives->setText( documentProxy->metaData(UBSettings::sessionObjectives).toString());
//    mpKeywords->setText( documentProxy->metaData(UBSettings::sessionKeywords).toString());

//    int currentIndex = mpSchoolLevelBox->findText(documentProxy->metaData(UBSettings::sessionGradeLevel).toString());
//    mpSchoolLevelBox->setCurrentIndex((currentIndex != -1) ? currentIndex : 0);

//    currentIndex = mpSchoolSubjectsBox->findText(documentProxy->metaData(UBSettings::sessionSubjects).toString());
//    mpSchoolSubjectsBox->setCurrentIndex((currentIndex != -1) ? currentIndex : 0);

//    currentIndex = mpSchoolTypeBox->findText(documentProxy->metaData(UBSettings::sessionType).toString());
//    mpSchoolTypeBox->setCurrentIndex((currentIndex != -1) ? currentIndex : 0);

//    currentIndex = documentProxy->metaData(UBSettings::sessionLicence).toInt();
//    mpLicenceBox->setCurrentIndex((currentIndex != -1) ? currentIndex : 0);
}

void UBTeacherGuidePageZeroWidget::persistData()
{
    // check necessary because at document closing hide event is send after boardcontroller set
    // to NULL
//    if (UBApplication::boardController) {
//        UBDocumentProxy* documentProxy = UBApplication::boardController->selectedDocument();
//        documentProxy->setMetaData(qsMetaTitle, mpSessionTitle->text());
//        documentProxy->setMetaData(qsMetaAuthor, mpAuthors->text());
//        documentProxy->setMetaData(qsMetaObjectives, mpObjectives->text());
//        documentProxy->setMetaData(qsMetaKeywords, mpKeywords->text());
//        documentProxy->setMetaData(qsMetaGradeLevel, mpSchoolLevelBox->currentText());
//        documentProxy->setMetaData(qsMetaSubjects, mpSchoolSubjectsBox->currentText());
//        documentProxy->setMetaData(qsMetaType, mpSchoolTypeBox->currentText());
//        documentProxy->setMetaData(qsMetaLicense, mpLicenceBox->currentIndex());
//    }
}

void UBTeacherGuidePageZeroWidget::updateSceneTitle()
{
    QString sessionTitle = mpSessionTitle->text();
    //if (!sessionTitle.isEmpty())
        //UBApplication::boardController->activeScene()->textForObjectName(mpSessionTitle->text());
}

void UBTeacherGuidePageZeroWidget::switchToMode(tUBTGZeroPageMode mode)
{
    if (mode == tUBTGZeroPageMode_EDITION) {
        QString inputStyleSheet("QTextEdit { background: white; border-radius: 10px; border: 2px;}");
        mpModePushButton->hide();
        mpSessionTitle->setReadOnly(false);
        mpSessionTitle->managePlaceholder(true);
        mpSessionTitle->setStyleSheet(inputStyleSheet);
        QFont titleFont(QApplication::font().family(), 11, -1);
        mpSessionTitle->document()->setDefaultFont(titleFont);
        mpAuthors->setReadOnly(false);
        mpAuthors->managePlaceholder(false);
        mpAuthors->setStyleSheet(inputStyleSheet);
        mpObjectives->setReadOnly(false);
        mpObjectives->managePlaceholder(false);
        mpObjectives->setStyleSheet(inputStyleSheet);
        mpKeywords->setReadOnly(false);
        mpKeywords->managePlaceholder(false);
        mpKeywords->setStyleSheet(inputStyleSheet);
        mpSchoolLevelValueLabel->hide();
        mpSchoolLevelBox->show();
        mpSchoolSubjectsValueLabel->hide();
        mpSchoolSubjectsBox->show();
        mpSchoolTypeValueLabel->hide();
        mpSchoolTypeBox->show();
        mpLicenceIcon->hide();
        mpLicenceValueLabel->hide();
        mpLicenceBox->show();
    }
    else {
        QString inputStyleSheet( "QTextEdit { background: transparent; border: none;}");
        mpModePushButton->show();
        mpSessionTitle->showText(mpSessionTitle->text());
        mpSessionTitle->setStyleSheet(inputStyleSheet);
        updateSceneTitle();
        QFont titleFont(QApplication::font().family(), 14, 1);
        mpSessionTitle->document()->setDefaultFont(titleFont);
        mpAuthors->setStyleSheet(inputStyleSheet);
        mpAuthors->setTextColor(QColor(Qt::black));
        mpAuthors->showText(mpAuthors->text());
        mpObjectives->setStyleSheet(inputStyleSheet);
        mpObjectives->setTextColor(QColor(Qt::black));
        mpObjectives->showText(mpObjectives->text());
        mpKeywords->setStyleSheet(inputStyleSheet);
        mpKeywords->setTextColor(QColor(Qt::black));
        mpKeywords->showText(mpKeywords->text());
        mpSchoolLevelValueLabel->setText(mpSchoolLevelBox->currentText());
        mpSchoolLevelValueLabel->show();
        mpSchoolLevelBox->hide();
        mpSchoolSubjectsValueLabel->setText(mpSchoolSubjectsBox->currentText());
        mpSchoolSubjectsValueLabel->show();
        mpSchoolSubjectsBox->hide();
        mpSchoolTypeValueLabel->setText(mpSchoolTypeBox->currentText());
        mpSchoolTypeValueLabel->show();
        mpSchoolTypeBox->hide();
        mpLicenceValueLabel->setText(mpLicenceBox->currentText());
        QString licenceIconPath = mpLicenceBox->itemData(mpLicenceBox->currentIndex()).toString();
        if (!licenceIconPath.isEmpty()) {
            mpLicenceIcon->setPixmap(QPixmap(licenceIconPath));
            mpLicenceIcon->show();
        }
        mpLicenceValueLabel->show();
        mpLicenceBox->hide();
        persistData();
    }
    update();
}

QVector<tUBGEElementNode*> UBTeacherGuidePageZeroWidget::getData()
{
    QVector<tUBGEElementNode*> result;
    tUBGEElementNode* elementNode = new tUBGEElementNode();
    elementNode->name = "sessionTitle";
    elementNode->attributes.insert("value", mpSessionTitle->text());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "authors";
    elementNode->attributes.insert("value", mpAuthors->text());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "creationDate";
    elementNode->attributes.insert("value", mpCreationLabel->text());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "lastModifiedDate";
    elementNode->attributes.insert("value", mpLastModifiedLabel->text());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "goals";
    elementNode->attributes.insert("value", mpObjectives->text());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "keywords";
    elementNode->attributes.insert("value", mpKeywords->text());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "schoolLevel";
    elementNode->attributes.insert("value", mpSchoolLevelBox->currentText());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "schoolBranch";
    elementNode->attributes.insert("value", mpSchoolSubjectsBox->currentText());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "schoolType";
    elementNode->attributes.insert("value", mpSchoolTypeBox->currentText());
    result << elementNode;

    elementNode = new tUBGEElementNode();
    elementNode->name = "licence";
    elementNode->attributes.insert("value", QString("%1").arg(mpLicenceBox->currentIndex()));
    result << elementNode;
    return result;
}

bool UBTeacherGuidePageZeroWidget::isModified()
{
    bool result = false;
    result |= mpSessionTitle->text().length() > 0;
    result |= mpAuthors->text().length() > 0;
    result |= mpObjectives->text().length() > 0;
    result |= mpKeywords->text().length() > 0;
    result |= mpSchoolLevelBox->currentIndex() > 0;
    result |= mpSchoolSubjectsBox->currentIndex() > 0;
    result |= mpSchoolTypeBox->currentIndex() > 0;
    result |= mpLicenceBox->currentIndex() > 0;
    return result;
}

void UBTeacherGuidePageZeroWidget::resizeEvent(QResizeEvent* ev)
{
    emit resized();
    QWidget::resizeEvent(ev);
}
