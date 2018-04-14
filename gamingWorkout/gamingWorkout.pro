#-------------------------------------------------
#
# Project created by QtCreator 2018-04-13T17:26:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gamingWorkout
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    	semaforo/semaforo.cpp \
    rastros/rastros.cpp \
    caesGatos/caesgatos.cpp \
    avanco/avanco.cpp \
    Produto/produto.cpp

HEADERS += \
        mainwindow.h \
    	semaforo/semaforo.h \
    rastros/rastros.h \
    caesGatos/caesgatos.h \
    avanco/avanco.h \
    Produto/produto.h

FORMS += \
        mainwindow.ui \
        semaforo/semaforo.ui \
    rastros/rastros.ui \
    caesGatos/caesgatos.ui \
    avanco/avanco.ui \
    Produto/produto.ui


RESOURCES += \
    	semaforo/semaforo.qrc \
    rastros/rastros.qrc \
    caesGatos/caesgatos.qrc
