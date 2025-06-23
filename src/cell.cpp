#include "cell.h"

cell::cell(QPushButton *parent) : QPushButton{parent}
{

}

cell::cell(ushort x, ushort y, ushort minesAround, bool isMine) :
    m_current(status::deflt),
    m_x(x),
    m_y(y),
    m_minesAround(minesAround),
    m_isMine(isMine)
{

}


