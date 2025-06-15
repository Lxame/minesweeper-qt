#include <QRandomGenerator>
#include <QGridLayout>

#include <iostream>

#include "field.h"

field::field(QWidget *parent) : QWidget{parent}
{

}

field::field(ushort width, ushort height, ushort minesCount)
    : m_width(width), m_height(height), m_minesCount(minesCount)
{
    formField();
    initCells();
}

bool field::formField()
{
    fld.assign(m_height, std::vector<int>(m_width, 0));

    generateMines();

    for (const auto &col : fld)
    {
        for (const auto &row : col)
        {
            std::cout << row << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return true;
}

void field::generateMines()
{  
    ushort minesCreated = 0;

    while (minesCreated < m_minesCount)
    {
        int x = QRandomGenerator::global()->bounded(0, m_width);
        int y = QRandomGenerator::global()->bounded(0, m_height);

        if (fld.at(y).at(x) == 0)
        {
            fld.at(y).at(x) = -1;
            ++minesCreated;
        }
    }
}

void field::initCells()
{
    for (ushort y = 0; y < m_height; ++y)
    {
        for (ushort x = 0; x < m_width; ++x)
        {
            bool isMine = fld.at(y).at(x) == -1;
            cell newCell(x, y, isMine ? -1 : countMinesAroundCell(x, y), isMine);

            if (isMine)
            {
                std::cout << -1 << " ";
            }
        }
        std::cout << std::endl;
    }

    //QGridLayout *grid = new QGridLayout();

}

ushort field::countMinesAroundCell(ushort x, ushort y)
{
    ushort mines_count = 0;
    for (int col = x - 1; col <= x + 1; ++col)
    {
        for (int row = y - 1; row <= y + 1; ++row)
        {
            if (row >= 0 && row < m_height && col >= 0 && col < m_width && fld.at(row).at(col) == -1)
            {
                ++mines_count;
            }
        }
    }
    std::cout << mines_count << " ";
    return mines_count;
}
