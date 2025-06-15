#include <QRandomGenerator>

#include <iostream>

#include "field.h"

field::field(QWidget *parent) : QWidget{parent}
{

}

field::field(ushort width, ushort height, ushort minesCount)
    : m_width(width), m_height(height), m_minesCount(minesCount)
{
    formField();
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

    return true;
}

void field::generateMines()
{  
    ushort minesCreated = 0;

    while (minesCreated < m_minesCount)
    {
        int x = QRandomGenerator::global()->bounded(0, m_width - 1);
        int y = QRandomGenerator::global()->bounded(0, m_height - 1);

        if (fld.at(y).at(x) == 0)
        {
            fld.at(y).at(x) = -1;
            ++minesCreated;
        }
    }
}
