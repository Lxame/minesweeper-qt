#include "cell.h"

cell::cell(ushort x, ushort y, ushort minesCount, bool isMine) :
    m_x(x), m_y(y), m_minesAround(minesCount), m_isMine(isMine)
{

}
