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
    int scale = 32;
    QIcon def       (QPixmap(":images/default.png")     .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon one       (QPixmap(":images/one.png")         .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon two       (QPixmap(":images/two.png")         .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon three     (QPixmap(":images/three.png")       .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon four      (QPixmap(":images/four.png")        .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon five      (QPixmap(":images/five.png")        .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon six       (QPixmap(":images/six.png")         .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon seven     (QPixmap(":images/seven.png")       .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon eight     (QPixmap(":images/eight.png")       .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon empty     (QPixmap(":images/empty.png")       .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon flag      (QPixmap(":images/flag.png")        .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon red_flag  (QPixmap(":images/red_flag.png")    .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon mine      (QPixmap(":images/mine.png")        .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QIcon mine_boom (QPixmap(":images/mine_boom.png")   .scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    std::cout << "insert..." << std::endl;
    iqons.insert(ICON::def, def);
    iqons.insert(ICON::one, one);
    iqons.insert(ICON::two, two);
    iqons.insert(ICON::three, three);
    iqons.insert(ICON::four, four);
    iqons.insert(ICON::five, five);
    iqons.insert(ICON::six, six);
    iqons.insert(ICON::seven, seven);
    iqons.insert(ICON::eight, eight);
    iqons.insert(ICON::empty, empty);
    iqons.insert(ICON::flag, flag);
    iqons.insert(ICON::red_flag, red_flag);
    iqons.insert(ICON::mine, mine);
    iqons.insert(ICON::mine_boom, mine_boom);
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
        QVector<cell*> row;
        for (ushort x = 0; x < m_width; ++x)
        {
            bool isMine = fld.at(y).at(x) == -1;
            cell *newCell = new cell(x, y, isMine ? -1 : countMinesAroundCell(x, y), isMine);
            newCell->setIcon(iqons.value(ICON::def));
            int size = 32;
            newCell->setFixedSize(size, size);
            newCell->setIconSize(QSize(size, size));

            connect(newCell, SIGNAL(pressed()),      this, SLOT(leftPressed()));
            connect(newCell, SIGNAL(released()),     this, SLOT(leftReleased()));
            connect(newCell, SIGNAL(rightClicked()), this, SLOT(rightClick()));

            if (isMine)
            {
                std::cout << -1 << " ";
            }

            row.push_back(newCell);
            grid->addWidget(newCell, y, x);
        }
        cells.push_back(row);
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

void field::leftPressed()
{
    cell *c = qobject_cast<cell*>(sender());

    ushort mines = c->mines();
    ushort x = c->getX();
    ushort y = c->getY(); 

    switch (c->getStatus()) 
    {
    case cell::status::deflt:
        c->setIcon(iqons.value(ICON::empty));
        break;
    case cell::status::flag:
        break;
    case cell::status::open:
        lightNearest(x, y, true);
        break;
    default:
        break;
    }
}

void field::leftReleased()
{
    cell *c = qobject_cast<cell*>(sender());

    std::cout << "LEFT button clicked x: " << c->getX() << " y: " << c->getY() << "\t";
    std::cout << "status: " << c->getStatus() << std::endl;

    ushort mines = c->mines();
    ushort x = c->getX();
    ushort y = c->getY(); 

    switch (c->getStatus()) 
    {
    case cell::status::deflt:
        if (c->isMine())
        {
            // lose
            c->setIcon(iqons.value(ICON::mine_boom));
            lose();
        }
        else
        {
            c->setIcon(iqons.value(static_cast<ICON>(mines)));
            c->setStatus(cell::status::open);
            if (mines == 0)
            {
                openNearest(x, y);
            }
        }
        break;
    case cell::status::flag:
        break;
    case cell::status::open:
        lightNearest(x, y, false);
        if (mines != 0)
        {
            // pick nearest
        }
        break;
    default:
        break;
    }
}

void field::rightClick()
{
    cell *c = qobject_cast<cell*>(sender());

    std::cout << "RIGHT button clicked x: " << c->getX() << " y: " << c->getY() << "\t";
    std::cout << "status: " << c->getStatus() << std::endl;

    switch (c->getStatus()) 
    {
    case cell::status::deflt:
        c->setIcon(iqons.value(ICON::flag));
        c->setStatus(cell::status::flag);
        break;
    case cell::status::flag:
        c->setIcon(iqons.value(ICON::def));
        c->setStatus(cell::status::deflt);
        break;
    case cell::status::open:
        break;
    default:
        break;
    }
}

void field::openNearest(ushort x, ushort y)
{
    for (int col = x - 1; col <= x + 1; ++col)
    {
        for (int row = y - 1; row <= y + 1; ++row)
        {
            if (row >= 0 && row < m_height && col >= 0 && col < m_width && fld.at(row).at(col) == 0)
            {
                cell *c = cells.at(row).at(col);
                if (c->getStatus() == cell::status::deflt)
                {
                    c->setStatus(cell::status::open);

                    const ushort mines = c->mines();
                    c->setIcon(iqons.value(static_cast<ICON>(mines)));
                    if (mines == 0)
                    {
                        openNearest(c->getX(), c->getY());
                    }
                }
            }
        }
    }
}

void field::lightNearest(ushort x, ushort y, bool show)
{
    for (int col = x - 1; col <= x + 1; ++col)
    {
        for (int row = y - 1; row <= y + 1; ++row)
        {
            if (row >= 0 && row < m_height && col >= 0 && col < m_width)
            {
                cell *c = cells.at(row).at(col);
                if (c->getStatus() == cell::status::deflt)
                {
                    if (show)
                    {
                        c->setIcon(iqons.value(ICON::empty));
                    }
                    else
                    {
                        c->setIcon(iqons.value(ICON::def));
                    }
                }
            }
        }
    }
}

void field::lose()
{
    std::cout << "You lose" << std::endl;
}

void field::win()
{
    std::cout << "You win!!!" << std::endl;
}
