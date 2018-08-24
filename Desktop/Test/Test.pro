QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testcase.cpp \
    ../Fallturm/parabola.cpp

unix:!macx: LIBS += -larmadillo

HEADERS += \
    ../Fallturm/parabola.h

unix:!macx: LIBS += -larmadillo
