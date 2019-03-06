######################################################################
# Automatically generated by qmake (3.1) Sat Mar 2 17:24:42 2019
######################################################################

TEMPLATE = app
TARGET = memManager
INCLUDEPATH += .

QT += widgets
QT += core

CONFIG += c++11, console

win32:QMAKE_LFALGS += -shared
# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += mainwidget.h MemoryManager.h Process.h MemSpaces.h
SOURCES += main.cpp mainwidget.cpp MemoryManager.cpp Process.cpp MemSpaces.cpp