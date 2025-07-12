#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>

#include "field.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {};

private:
    QPushButton *m_pStartBtn;
    QComboBox *m_pDifficultyCmb;

    field* game;

private slots:
    void newGame();

};

#endif // MAINWINDOW_H
