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
    m_pDifficultyCmb->addItem("Easy", QVariant(1));
    m_pDifficultyCmb->addItem("Medium", QVariant(2));
    m_pDifficultyCmb->addItem("Hard", QVariant(3));
    m_pDifficultyCmb->setFixedSize(100, 25);

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->setSpacing(10);
    pLayout->setAlignment(Qt::AlignCenter);
    pLayout->addWidget(m_pStartBtn);
    pLayout->addWidget(pChooseDifficultyLbl);
    pLayout->addWidget(m_pDifficultyCmb);

    setLayout(pLayout);

    connect(m_pStartBtn, SIGNAL(clicked()), this, SLOT(newGame()));
}

void MainWindow::newGame()
{
    ushort width = 9, height = 9, mines = 10;

    switch ((m_pDifficultyCmb->currentData().toInt()))
    {
    case 1:
        width = 9;
        height = 9;
        mines = 10;
        break;
    case 2:
        width = 16;
        height = 16;
        mines = 40;
        break;
    case 3:
        width = 30;
        height = 16;
        mines = 99;
        break;
    default:
        break;
    }

    field* newGame = new field(width, height, mines);
    newGame->show();
}
