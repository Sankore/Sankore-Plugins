TEMPLATE  = lib
CONFIG   += plugin
QT       += core gui
QT       += webkit
QT       += svg
QT       += network
QT       += phonon
QT       += xml
QT       += script
QT       += xmlpatterns

# Build folders configuration
BUILD_DIR = build
macx:BUILD_DIR = $$BUILD_DIR/macx
win32:BUILD_DIR = $$BUILD_DIR/win32
linux-g++*:BUILD_DIR = $$BUILD_DIR/linux

CONFIG(debug, debug|release):BUILD_DIR = $$BUILD_DIR/debug
CONFIG(release, debug|release) {
   BUILD_DIR = $$BUILD_DIR/release
}
DESTDIR = $$BUILD_DIR/product
OBJECTS_DIR = $$BUILD_DIR/objects
MOC_DIR = $$BUILD_DIR/moc
RCC_DIR = $$BUILD_DIR/rcc
UI_DIR = $$BUILD_DIR/ui

# Static libraries by this plugin
SANKOREAPI_BASEPATH = $$PWD/../../Sankore-API
SANKOREAPI_PATH = $$SANKOREAPI_BASEPATH/build
macx:SANKOREAPI_PATH = $$SANKOREAPI_PATH/macx
win32:SANKOREAPI_PATH = $$SANKOREAPI_PATH/win32
linux-g++*:SANKOREAPI_PATH = $$SANKOREAPI_PATH/linux
CONFIG(debug, debug|release):SANKOREAPI_PATH = $$SANKOREAPI_PATH/debug/product
CONFIG(release, debug|release) {
   SANKOREAPI_PATH = $$SANKOREAPI_PATH/release/product
}
LIBS += -L$$SANKOREAPI_PATH -lSankoreAPI
INCLUDEPATH += $$SANKOREAPI_BASEPATH

# Source & header files
HEADERS  += TeacherBarPlugin.h \
    UBTGDockWidget.h
SOURCES  += TeacherBarPlugin.cpp \
    main.cpp \
    UBTGDockWidget.cpp
TARGET = $$qtLibraryTarget(TeacherBar)
