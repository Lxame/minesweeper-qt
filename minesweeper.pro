QT      += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++17

SOURCES += \
    .\src\main.cpp \
    .\src\mainwindow.cpp \
    src/cell.cpp \
    src/field.cpp

HEADERS += \
    .\src\mainwindow.h \
    src/cell.h \
    src/field.h
