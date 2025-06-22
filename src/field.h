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
    ushort m_width;
    ushort m_height;
    ushort m_minesCount;
    std::vector<std::vector<int>> fld;
    QVector<cell> *cells;
    QMap<int, QIcon> iqons;

private:
    bool formField();
    void generateMines();
    void initCells();
    void initRes();
    ushort countMinesAroundCell(ushort x, ushort y);

private slots:
    void processClick();
};

#endif // FIELD_H
