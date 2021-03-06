#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T16:19:55
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Pluri_Notes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    Notes.cpp \
    Memento.cpp \
    noteWindow.cpp \
    relations.cpp\
    explorateurWindow.cpp \
    RelationWindow.cpp \
    arborescence.cpp

HEADERS  += mainwindow.h \
    Notes.h \
    Memento.h \
    noteWindow.h \
    relations.h\
    explorateurWindow.h \
    RelationWindow.h \
    arborescence.h

FORMS    += mainwindow.ui
