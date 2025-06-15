#ifndef CELL_H
#define CELL_H

#include <QAbstractButton>

class cell : public QAbstractButton
{
public:
    cell(ushort x, ushort y, ushort minesCount, bool isMine);

private:
    enum Status
    {
        empty = 0,
        open = 1,
        flag = 2,
    };
    ushort m_x, m_y;
    ushort m_minesAround;
    bool m_isMine;
};

#endif // CELL_H
