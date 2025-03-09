#include "mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    m_pStartBtn = new QPushButton("Start!");
    m_pStartBtn->setMinimumSize(100, 20);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(m_pStartBtn);

    setLayout(pLayout);
}

MainWindow::~MainWindow() {}
