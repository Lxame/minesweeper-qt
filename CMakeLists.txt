cmake_minimum_required(VERSION 3.16)

project(minesweeper-qt VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)           # Автоматическая генерация moc-файлов
set(CMAKE_AUTORCC ON)           # Авто-подключение ресурсов (если есть)
set(CMAKE_AUTOUIC ON)           # Авто-подключение .ui (если есть)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Widgets)

add_executable(minesweeper-qt
    src/main.cpp
    src/cell.cpp
    src/cell.h
    src/field.cpp
    src/field.h
    src/mainwindow.cpp
    src/mainwindow.h
    src/lcdmines.cpp
    src/lcdmines.h
    src/lcdtimer.cpp
    src/lcdtimer.h
    res/res.qrc
)

target_link_libraries(minesweeper-qt PRIVATE Qt5::Core)
target_link_libraries(minesweeper-qt PRIVATE Qt5::Widgets)