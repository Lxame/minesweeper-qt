#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
//#include <list>

#include "cell.h"

class field : public QWidget
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = nullptr);
    field(ushort width, ushort height, ushort minesCount);

private:
    ushort m_width;
    ushort m_height;
    ushort m_minesCount;
    std::vector<std::vector<int>> fld;
    QVector<cell> *cells;

private:
    bool formField();
    void generateMines();
    void initCells();
    ushort countMinesAroundCell(ushort x, ushort y);

signals:
};

#endif // FIELD_H
