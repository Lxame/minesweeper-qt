#include "lcdmines.h"

LCDmines::LCDmines(QWidget *parent) : QLCDNumber(parent)
{

}

LCDmines::LCDmines(qint8 mines, int width, int height, QWidget *parent) : QLCDNumber(parent), m_minesLeft(mines)
{
    setDigitCount(3);
    setFixedSize(width, height);
    display(mines);
}

void LCDmines::increase()
{
    m_minesLeft++;
    display(m_minesLeft);
}

void LCDmines::decrease()
{
    m_minesLeft--;
    display(m_minesLeft);
}

void LCDmines::reset(qint8 mines)
{
    m_minesLeft = mines;
    display(m_minesLeft);
}