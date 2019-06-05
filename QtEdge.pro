#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T10:15:46
#
#-------------------------------------------------

QT       += core gui winextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtEdge
TEMPLATE = app

LIBS += User32.lib


SOURCES += main.cpp\
        widget.cpp \
    Source/QtEdgeNativeEventFilter.cpp \
    Source/QtEdgeFrameLessWidgetHelper.cpp \
    Source/QtEdgeFrameLessHelper.cpp \
    Source/QtEdgeIconHelper.cpp

HEADERS  += widget.h \
    Source/QtEdgeNativeEventFilter.h \
    Source/QtEdgeFrameLessWidgetHelper.h \
    Source/QtEdgeFrameLessHelper.h \
    Source/QtEdgeIconHelper.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
