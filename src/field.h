#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QIcon>
#include <QMap>
//#include <list>

#include "cell.h"

class field : public QWidget
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = nullptr);
    field(ushort width, ushort height, ushort minesCount);

private:
    enum ICON
    {
        def = -1,
        empty = 0,
        one = 1,
        two = 2,
        three = 3,
        four = 4,
        five = 5,
        six = 6,
        seven = 7,
        eight = 8,
        flag = 16,
        red_flag = 32,
        mine = 64,
        mine_boom = 128
    };
    ushort m_width;
    ushort m_height;
    ushort m_minesCount;
    std::vector<std::vector<int>> fld;
    QVector<cell> *cells;
    QMap<ICON, QIcon> iqons;

private:
    bool formField();
    void generateMines();
    void initCells();
    void initRes();
    ushort countMinesAroundCell(ushort x, ushort y);
    void lose();
    void win();

private slots:
    void leftClick();
    void rightClick();
};

#endif // FIELD_H
