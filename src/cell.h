#ifndef CELL_H
#define CELL_H

#include <QPushButton>>

class cell : public QPushButton
{
public:
    cell(ushort x, ushort y, ushort minesAround, bool isMine);

private:
    enum Status
    {
        deflt = 0,
        open = 1,
        flag = 2,
    };
    ushort m_x, m_y;
    ushort m_minesAround;
    bool m_isMine;
};

#endif // CELL_H
