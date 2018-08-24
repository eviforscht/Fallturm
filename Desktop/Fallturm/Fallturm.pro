#-------------------------------------------------
#
# Project created by QtCreator 2018-01-30T17:02:10
#
#-------------------------------------------------

QT       += core gui widgets charts multimedia multimediawidgets charts serialport
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fallturm
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
    logger.cpp \
    fallturmexception.cpp \
    settingsdialog.cpp \
    plot.cpp \
    parabola.cpp \
    mainwindow.cpp


HEADERS += \
        mainwindow.h \
    main.h \
    logger.h \
    fallturmexception.h \
    settingsdialog.h \
    plot.h \
    parabola.h

FORMS += \
        mainwindow.ui \
    settingsdialog.ui


#TODO
# add -O3 option for compiling, for better armadillo performance

#linux build options
unix:!macx: LIBS += -larmadillo


#windows build options
win32{

LIBS += -L$$PWD/lib/armadillo-9.100.5/ -lblas_win64_MT -llapack_win64_MT -larmadillo

INCLUDEPATH += $$PWD/lib/armadillo-9.100.5/include/
DEPENDPATH += $$PWD/lib/armadillo-9.100.5/include/
INCLUDEPATH += $$PWD/lib/armadillo-9.100.5/include/armadillo_bits/
DEPENDPATH += $$PWD/lib/armadillo-9.100.5/include/armadillo_bits/
}

