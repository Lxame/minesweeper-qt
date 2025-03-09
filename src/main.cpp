#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("MineSweeper");
    //w.resize(800, 600);
    w.setFixedSize(400, 300);
    w.show();
    return a.exec();
}
