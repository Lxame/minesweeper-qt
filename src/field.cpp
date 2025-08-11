#include <QRandomGenerator>
#include <QTimer>
#include <QStyle>

#include <iostream>

#include "field.h"

const int SIZE = 32;

field::field(QWidget *parent) : QWidget(parent)
{

}

field::field(quint16 width, quint16 height, quint16 minesCount) : 
    m_width(width), 
    m_height(height),
    m_minesCount(minesCount),
    m_flagsPlaced(0),
    m_correctedFlagsPlaced(0) 
{
    initRes();
    formField();
    initField();
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
    fld.clear();
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
    quint16 minesCreated = 0;

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

void field::initField()
{
    mainLayout = new QVBoxLayout(this);
    controlsLayout = new QHBoxLayout(this);

    lcdmines = new LCDmines(m_minesCount, SIZE * 3, SIZE * 2, this);

    smile = new QPushButton("restart", this);
    connect(smile, SIGNAL(clicked()), this, SLOT(restartGame()));

    timer = new LCDtimer(SIZE * 3, SIZE * 2, this);
    timer->start();

    controlsLayout->addWidget(lcdmines,   0, Qt::AlignLeft);
    controlsLayout->addWidget(smile,      0, Qt::AlignCenter);
    controlsLayout->addWidget(timer,      0, Qt::AlignRight);
    controlsLayout->setMargin(SIZE / 2);

    // fieldLayout = 
    initCells();

    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(fieldLayout);

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setMargin(SIZE / 2);

    this->setLayout(mainLayout);
}

QGridLayout* field::initCells()
{
    // QGridLayout *grid = new QGridLayout(this);
    fieldLayout = new QGridLayout(this);
    int SIZE = 32;

    for (quint16 y = 0; y < m_height; ++y)
    {
        QVector<cell*> row;
        for (quint16 x = 0; x < m_width; ++x)
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
            fieldLayout->addWidget(newCell, y, x);
        }
        cells.push_back(row);
        std::cout << std::endl;
    }

    fieldLayout->setSpacing(0);
    fieldLayout->setContentsMargins(0, 0, 0, 0);
	fieldLayout->setSizeConstraint(QLayout::SetFixedSize);
    fieldLayout->setMargin(SIZE / 2);

    return fieldLayout;
}

quint16 field::countMinesAroundCell(quint16 x, quint16 y)
{
    quint16 mines_count = 0;
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

    quint16 mines = c->minesAround();
    quint16 x = c->getX();
    quint16 y = c->getY(); 

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

    quint16 mines = c->minesAround();
    quint16 x = c->getX();
    quint16 y = c->getY(); 

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
    quint16 x = c->getX();
    quint16 y = c->getY();

    std::cout << "RIGHT button clicked x: " << c->getX() << " y: " << c->getY() << "\t";
    std::cout << "status: " << c->getStatus() << std::endl;

    switch (c->getStatus()) 
    {
    case cell::status::deflt:
        placeFlag(c, x, y);
        break;
    case cell::status::flag:
        removeFlag(c, x, y);
        break;
    case cell::status::open:
        break;
    default:
        break;
    }

    if (m_correctedFlagsPlaced == m_minesCount && m_correctedFlagsPlaced == m_flagsPlaced)
    {
        win();
    }
}

void field::placeFlag(cell* c, const quint16& x, const quint16& y)
{
    c->setIcon(iqons.value(ICON::flag));
    c->setStatus(cell::status::flag);
    ++m_flagsPlaced;
    lcdmines->decrease();
    if(c->isMine())
        ++m_correctedFlagsPlaced;
    updateNearestFlagCount(x, y, true);
}

void field::removeFlag(cell* c, const quint16& x, const quint16& y)
{
    c->setIcon(iqons.value(ICON::def));
    c->setStatus(cell::status::deflt);
    --m_flagsPlaced;
    lcdmines->increase();
    if(c->isMine())
        --m_correctedFlagsPlaced;
    updateNearestFlagCount(x, y, false);
}

void field::openNearest(quint16 x, quint16 y)
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
                        const quint16 mines = c->minesAround();
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

void field::lightNearest(quint16 x, quint16 y, bool show)
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

void field::updateNearestFlagCount(quint16 x, quint16 y, bool increase)
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
            }
        }
    }
}

void field::disableLayout(QLayout* layout, bool disable) 
{
    for (int i = 0; i < layout->count(); ++i) 
    {
        QWidget* widget = layout->itemAt(i)->widget();
        if (widget)
        {
            widget->setDisabled(disable);
        }
    }
}

void field::lose(quint16 x, quint16 y)
{
    std::cout << "You lose" << std::endl;
    smile->setText("lose :(");

    cell* c = cells.at(y).at(x);
    if (c->getStatus() == cell::status::deflt)
    {
        c->setStatus(cell::status::open);
        c->setIcon(iqons.value(ICON::mine_boom));
    }
    
    timer->stop();
    updateFieldAfterLose();
    disableLayout(fieldLayout, true);
}

void field::updateFieldAfterLose()
{
    for (quint16 y = 0; y < m_height; ++y)
    {
        for (quint16 x = 0; x < m_width; ++x)
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
    smile->setText("win :)");
    timer->stop();
}

void field::restartGame()
{
    formField();
    resetCells();
    disableLayout(fieldLayout, false);

    timer->reset();
    timer->start();

    lcdmines->reset(m_minesCount);

    smile->setText("restart");
}

void field::resetCells()
{
    for (quint16 y = 0; y < m_height; ++y)
    {
        for (quint16 x = 0; x < m_width; ++x)
        {
            cell* c = cells.at(y).at(x);

            c->setStatus(cell::status::deflt);
            c->setIcon(iqons.value(ICON::def));
            c->setMine(fld.at(y).at(x) == -1);
            c->setMinesAround(c->isMine() ? -1 : countMinesAroundCell(x, y));
            c->resetFlagsCount();
        }
    }
}
