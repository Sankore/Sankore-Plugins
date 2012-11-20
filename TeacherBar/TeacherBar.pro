#-------------------------------------------------
#
# Project created by QtCreator 2012-11-07T15:10:53
#
#-------------------------------------------------
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

CORE_ROOT = ../../Sankore-3.1
CORE_SRC = $$CORE_ROOT/src

THIRD_PARTY_PATH=../../Sankore-ThirdParty

INCLUDEPATH += $$CORE_SRC
INCLUDEPATH += $$CORE_SRC/interfaces
INCLUDEPATH += $$CORE_SRC/customWidgets
INCLUDEPATH += $$CORE_SRC/devtools
INCLUDEPATH += $$CORE_SRC/globals
INCLUDEPATH += $$CORE_SRC/frameworks

include($$CORE_SRC/interfaces/interfaces.pri)
include($$CORE_SRC/customWidgets/customWidgets.pri)
include($$CORE_SRC/devtools/devtools.pri)
include($$CORE_SRC/globals/globals.pri)
include($$CORE_SRC/frameworks/frameworks.pri)

DEPENDPATH += $$THIRD_PARTY_PATH/quazip
INCLUDEPATH += $$THIRD_PARTY_PATH/quazip
include($$THIRD_PARTY_PATH/quazip/quazip.pri)

HEADERS  += TeacherBarPlugin.h \
    UBTGDockWidget.h
SOURCES  += TeacherBarPlugin.cpp \
    main.cpp \
    UBTGDockWidget.cpp
TARGET = $$qtLibraryTarget(TeacherBar)
