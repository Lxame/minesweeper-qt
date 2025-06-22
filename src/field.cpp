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
    initRes();
    formField();
    initCells();
}

void field::initRes()
{
    QIcon def(":images/default.png");
    QIcon one(":images/one.png");
    QIcon two(":images/two.png");
    QIcon three(":images/three.png");
    QIcon four(":images/four.png");
    QIcon five(":images/five.png");
    QIcon six(":images/six.png");
    QIcon seven(":images/seven.png");
    QIcon eight(":images/eight.png");
    QIcon nine(":images/nine.png");
    QIcon zero(":images/zero.png");
    QIcon flag(":images/flag.png");
    QIcon red_flag(":images/red_flag.png");
    QIcon mine(":images/mine.png");
    QIcon mine_boom(":images/mine_boom.png");

    std::cout << "insert..." << std::endl;
    iqons.insert(0, def);
    iqons.insert(1, one);
    iqons.insert(2, two);
    iqons.insert(3, three);
    iqons.insert(4, four);
    iqons.insert(5, five);
    iqons.insert(6, six);
    iqons.insert(7, seven);
    iqons.insert(8, eight);
    iqons.insert(9, nine);
    iqons.insert(10, zero);
    iqons.insert(11, flag);
    iqons.insert(12, red_flag);
    iqons.insert(-1, mine);
    iqons.insert(-2, mine_boom);
    std::cout << "insert completed" << std::endl;
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
    QGridLayout *grid = new QGridLayout();

    for (ushort y = 0; y < m_height; ++y)
    {
        for (ushort x = 0; x < m_width; ++x)
        {
            bool isMine = fld.at(y).at(x) == -1;
            cell *newCell = new cell(x, y, isMine ? -1 : countMinesAroundCell(x, y), isMine);
            newCell->setIcon(iqons.value(0));
            int size = 16;
            newCell->setFixedSize(size, size);
            newCell->setIconSize(this->size());

            connect(newCell, SIGNAL(clicked()), this, SLOT(processClick()));

            if (isMine)
            {
                std::cout << -1 << " ";
            }

            grid->addWidget(newCell, y, x);
        }
        std::cout << std::endl;
    }
    grid->setSpacing(0);
    this->setLayout(grid);
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

void field::processClick()
{
    sender();
    cell *c = qobject_cast<cell*>(sender());
    std::cout << "button clicked x: " << c->getX() << " y: " << c->getY() << std::endl;
}


