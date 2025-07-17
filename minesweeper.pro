QT += core gui widgets

TARGET = minesweeper

SOURCES += \
    src/main.cpp \
    src/cell.cpp \
    src/field.cpp \
    src/mainwindow.cpp \
    src/lcdmines.cpp \
    src/lcdtimer.cpp \

HEADERS += \
    src/cell.h \
    src/field.h \
    src/mainwindow.h \
    src/lcdmines.h \
    src/lcdtimer.h \

RESOURCES += res/res.qrc