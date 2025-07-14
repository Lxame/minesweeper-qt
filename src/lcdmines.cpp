#include "lcdmines.h"

LCDmines::LCDmines(QWidget *parent) : QLCDNumber(parent)
{

}

LCDmines::LCDmines(ushort mines, int width, int height, QWidget *parent) : QLCDNumber(parent), m_minesLeft(mines)
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