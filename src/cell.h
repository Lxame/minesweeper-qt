#ifndef CELL_H
#define CELL_H

#include <QAbstractButton>

class cell : public QAbstractButton
{
public:
    cell(ushort x, ushort y, ushort minesCount, bool isMine);

private:
    ushort m_uiX, m_uiY;
    ushort m_uiMinesCount;
    bool m_bIsMine;
};

#endif // CELL_H
