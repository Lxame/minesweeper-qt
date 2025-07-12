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

    QIcon def;
    def.addPixmap(QPixmap(":images/default.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    def.addPixmap(QPixmap(":images/default.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon one;
    one.addPixmap(QPixmap(":images/one.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    one.addPixmap(QPixmap(":images/one.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon two;
    two.addPixmap(QPixmap(":images/two.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    two.addPixmap(QPixmap(":images/two.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon three;
    three.addPixmap(QPixmap(":images/three.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    three.addPixmap(QPixmap(":images/three.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon four;
    four.addPixmap(QPixmap(":images/four.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    four.addPixmap(QPixmap(":images/four.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon five;
    five.addPixmap(QPixmap(":images/five.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    five.addPixmap(QPixmap(":images/five.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon six;
    six.addPixmap(QPixmap(":images/six.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    six.addPixmap(QPixmap(":images/six.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon seven;
    seven.addPixmap(QPixmap(":images/seven.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    seven.addPixmap(QPixmap(":images/seven.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon eight;
    eight.addPixmap(QPixmap(":images/eight.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    eight.addPixmap(QPixmap(":images/eight.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon empty;
    empty.addPixmap(QPixmap(":images/empty.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    empty.addPixmap(QPixmap(":images/empty.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon flag;
    flag.addPixmap(QPixmap(":images/flag.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    flag.addPixmap(QPixmap(":images/flag.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon red_flag;
    red_flag.addPixmap(QPixmap(":images/red_flag.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    red_flag.addPixmap(QPixmap(":images/red_flag.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon mine;
    mine.addPixmap(QPixmap(":images/mine.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    mine.addPixmap(QPixmap(":images/mine.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

    QIcon mine_boom;
    mine_boom.addPixmap(QPixmap(":images/mine_boom.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Normal);
    mine_boom.addPixmap(QPixmap(":images/mine_boom.png").scaled(scale, scale, Qt::KeepAspectRatio, Qt::SmoothTransformation), QIcon::Mode::Disabled);

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
    int SIZE = 32;

    for (ushort y = 0; y < m_height; ++y)
    {
        QVector<cell*> row;
        for (ushort x = 0; x < m_width; ++x)
        {
            bool isMine = fld.at(y).at(x) == -1;
            cell *newCell = new cell(x, y, isMine ? -1 : countMinesAroundCell(x, y), isMine);
            newCell->setIcon(iqons.value(ICON::def));
            newCell->setFixedSize(SIZE, SIZE);
            newCell->setIconSize(QSize(SIZE, SIZE));

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
    grid->setContentsMargins(0, 0, 0, 0);
	grid->setSizeConstraint(QLayout::SetFixedSize);
    grid->setMargin(SIZE / 2);

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
    std::cout << "status: " << c->getStatus() << "\t";
    std::cout << "flags: " << c->getFlagsCount() << "\t";
    std::cout << "\n";

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
            lose(x, y);
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
        if (c->getFlagsCount() == mines)
        {
            // pick nearest
            openNearest(x, y);
        }
        break;
    default:
        break;
    }
}

void field::rightClick()
{
    cell *c = qobject_cast<cell*>(sender());
    ushort x = c->getX();
    ushort y = c->getY();

    std::cout << "RIGHT button clicked x: " << c->getX() << " y: " << c->getY() << "\t";
    std::cout << "status: " << c->getStatus() << std::endl;

    switch (c->getStatus()) 
    {
    case cell::status::deflt:
        c->setIcon(iqons.value(ICON::flag));
        c->setStatus(cell::status::flag);
        updateNearestFlagCount(x, y, true);
        break;
    case cell::status::flag:
        c->setIcon(iqons.value(ICON::def));
        c->setStatus(cell::status::deflt);
        updateNearestFlagCount(x, y, false);
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
            if (col == x && row == y)
            {
                continue;
            }
            else if (row >= 0 && row < m_height && col >= 0 && col < m_width)
            {
                cell *c = cells.at(row).at(col);
                if (c->getStatus() == cell::status::deflt)
                {
                    if (c->isMine())
                    {
                        c->setIcon(iqons.value(ICON::mine_boom));
                        lose(x, y);
                    }
                    else
                    {
                        const ushort mines = c->mines();
                        c->setIcon(iqons.value(static_cast<ICON>(mines)));
                        c->setStatus(cell::status::open);

                        if (mines == 0)
                        {
                            openNearest(c->getX(), c->getY());
                        }
                    }
                }
                else if (c->getStatus() == cell::status::flag)
                {
                    if (!c->isMine())
                    {
                        c->setIcon(iqons.value(ICON::red_flag));
                        lose(x, y);
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
            if (col == x && row == y)
            {
                continue;
            }
            else if (row >= 0 && row < m_height && col >= 0 && col < m_width)
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

void field::updateNearestFlagCount(ushort x, ushort y, bool increase)
{
    for (int col = x - 1; col <= x + 1; ++col)
    {
        for (int row = y - 1; row <= y + 1; ++row)
        {
            if (col == x && row == y)
            {
                continue;
            }
            else if (row >= 0 && row < m_height && col >= 0 && col < m_width)
            {
                cell *c = cells.at(row).at(col);
                increase ? c->increaseFlagsCount() : c->decreaseFlagsCount();
                // if (increase)
                // {
                //     c->increaseFlagsCount();
                // }
                // else
                // {
                //     c->decreaseFlagsCount();
                // }
            }
        }
    }
}

void field::lose(ushort x, ushort y)
{
    std::cout << "You lose" << std::endl;

    cell* c = cells.at(y).at(x);
    if (c->getStatus() == cell::status::deflt)
    {
        c->setStatus(cell::status::open);
        c->setIcon(iqons.value(ICON::mine_boom));
    }
    
    updateFieldAfterLose();

    this->setEnabled(false);
}

void field::updateFieldAfterLose()
{
    for (ushort y = 0; y < m_height; ++y)
    {
        for (ushort x = 0; x < m_width; ++x)
        {
            cell* c = cells.at(y).at(x);
            bool isMine = c->isMine();

            switch (c->getStatus()) 
            {
            case cell::status::deflt:
                if (isMine)
                {
                    c->setIcon(iqons.value(ICON::mine));
                } 
                break;
            case cell::status::flag:
                if (!isMine)
                {
                    c->setIcon(iqons.value(ICON::red_flag));
                }
                break;
            case cell::status::open:
                break;
            default:
                break;
            }
        }
    }
}

void field::win()
{
    std::cout << "You win!!!" << std::endl;
}
