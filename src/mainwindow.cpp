#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    m_pStartBtn = new QPushButton("Start!");
    m_pStartBtn->setFixedSize(100, 25);

    QLabel *pChooseDifficultyLbl = new QLabel("Choose difficulty");
    pChooseDifficultyLbl->setAlignment(Qt::AlignCenter);

    m_pDifficultyCmb = new QComboBox();
    m_pDifficultyCmb->addItem("Easy");
    m_pDifficultyCmb->addItem("Medium");
    m_pDifficultyCmb->addItem("Hard");
    m_pDifficultyCmb->setFixedSize(100, 25);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setSpacing(10);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->addWidget(m_pStartBtn);
    pLayout->addWidget(pChooseDifficultyLbl);
    pLayout->addWidget(m_pDifficultyCmb);

    setLayout(pLayout);
}

MainWindow::~MainWindow() {}
