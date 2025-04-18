QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = karnaugh
TEMPLATE = app


SOURCES += main.cpp\
    inputnoofvariableswindow.cpp \
    kmap.cpp \
    kmapwindow.cpp \
    table.cpp

HEADERS  += \
    inputnoofvariableswindow.h \
    kmap.h \
    kmapwindow.h \
    table.h

FORMS += \
    inputnoofvariableswindow.ui \
    kmapwindow.ui

RESOURCES += \
    resource.qrc
