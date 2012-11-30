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
#include "UBTGWidget.h"

UBTGWidget::UBTGWidget(UBTGModel* pModel, QWidget* parent, const char* name):
    QStackedWidget(parent)
  , mpPageZeroWidget(NULL)
  , mpEditionWidget(NULL)
  , mpPresentationWidget(NULL)
  , mKeyboardActionFired(false)
{
    setObjectName(name);
    //setStyleSheet("background: #EEEEEE;border-radius: 10px;border: 2px solid #999999;");
    mpPageZeroWidget = new UBTeacherGuidePageZeroWidget(pModel, this);
    addWidget(mpPageZeroWidget);
//    if (UBSettings::settings()->teacherGuidePageZeroActivated->get().toBool()) {
//        mpPageZeroWidget = new UBTeacherGuidePageZeroWidget(this);
//        addWidget(mpPageZeroWidget);
//    }
//    if (UBSettings::settings()->teacherGuideLessonPagesActivated->get().toBool()) {
//        mpEditionWidget = new UBTeacherGuideEditionWidget(this);
//        addWidget(mpEditionWidget);
//        mpPresentationWidget = new UBTeacherGuidePresentationWidget(this);
//        addWidget(mpPresentationWidget);
//    }

    //connect(UBApplication::boardController->controlView(), SIGNAL(clickOnBoard()), this, SLOT(showPresentationMode()));
    connectToStylusPalette();
    //connect(UBApplication::boardController, SIGNAL(activeSceneChanged()), this, SLOT(onActiveSceneChanged()));
}

UBTGWidget::~UBTGWidget(){
    DELETEPTR(mpPageZeroWidget);
    DELETEPTR(mpEditionWidget);
    DELETEPTR(mpPresentationWidget);
}

void UBTGWidget::onActiveSceneChanged()
{
//    if (UBApplication::boardController->currentPage() == 0) {
//        if(mpPageZeroWidget->isModified())
//            mpPageZeroWidget->switchToMode(tUBTGZeroPageMode_PRESENTATION);
//        else
//            mpPageZeroWidget->switchToMode(tUBTGZeroPageMode_EDITION);

//        setCurrentWidget(mpPageZeroWidget);
//    }
//    else{
//        if(mpEditionWidget->isModified()){
//            mCurrentData = mpEditionWidget->getData();
//            mpPresentationWidget->showData(mCurrentData);
//            setCurrentWidget(mpPresentationWidget);
//        }
//        else
//            setCurrentWidget(mpEditionWidget);
//    }

}

void UBTGWidget::onTriggeredAction(bool checked)
{
    Q_UNUSED(checked);
    if(!mKeyboardActionFired)
        showPresentationMode();
    mKeyboardActionFired=false;
}

void UBTGWidget::onTriggeredKeyboardAction(bool checked)
{
    Q_UNUSED(checked);
    mKeyboardActionFired = true;
}

void UBTGWidget::connectToStylusPalette()
{
/*	connect(UBApplication::mainWindow->actionPen, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionEraser, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionMarker, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionPointer, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionPlay, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionZoomIn, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionZoomOut, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionCapture, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionHand, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionLine, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionText, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionSelector, SIGNAL(triggered(bool)), this, SLOT(onTriggeredAction(bool)));
    connect(UBApplication::mainWindow->actionVirtualKeyboard, SIGNAL(triggered(bool)), this, SLOT(onTriggeredKeyboardAction(bool)));
*/}

void UBTGWidget::showPresentationMode()
{
    if (currentWidget() == mpPageZeroWidget) {
        mCurrentData = mpPageZeroWidget->getData();
        mpPageZeroWidget->switchToMode(tUBTGZeroPageMode_PRESENTATION);
    }
    else if (currentWidget() == mpEditionWidget) {
        mCurrentData = mpEditionWidget->getData();
        mpPresentationWidget->showData(mCurrentData);
        setCurrentWidget(mpPresentationWidget);
    }
}

void UBTGWidget::changeMode()
{
    if (currentWidget() == mpEditionWidget)
        setCurrentWidget(mpPresentationWidget);
    else
        setCurrentWidget(mpEditionWidget);

}

bool UBTGWidget::isModified()
{
    if (currentWidget() == mpPageZeroWidget)
        return mpPageZeroWidget->isModified();
    else
        return mpEditionWidget->isModified();
}
