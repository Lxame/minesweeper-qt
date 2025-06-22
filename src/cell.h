#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class cell : public QPushButton
{
    Q_OBJECT
public:
    explicit cell(QPushButton *parent = nullptr);
    cell(ushort x, ushort y, ushort minesAround, bool isMine);

    ushort getX()
    {
        return m_x;
    }

    ushort getY()
    {
        return m_y;
    }

private:
    enum status
    {
        deflt = 0,
        open = 1,
        flag = 2,
    };
    status m_current;
    ushort m_x, m_y;
    ushort m_minesAround;
    bool m_isMine;
};

#endif // CELL_H
