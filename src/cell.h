#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QMouseEvent>

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

    ushort mines()
    {
        return m_minesAround;
    }

    bool isMine()
    {
        return m_isMine;
    }

    enum status
    {
        deflt = 0,
        open = 1,
        flag = 2,
    };

    status getStatus()
    {
        return m_current;
    }

    void setStatus(status stat)
    {
        m_current = stat;
    }

    void increaseFlagsCount()
    {
        if (m_flagsAround < 8)
            ++m_flagsAround;
    }

    void decreaseFlagsCount()
    {
        if (m_flagsAround > 0)
            --m_flagsAround;
    }

    ushort getFlagsCount()
    {
        return m_flagsAround;
    }

private:
    status m_current;
    ushort m_x, m_y;
    ushort m_minesAround;
    ushort m_flagsAround;
    bool m_isMine;

signals:
    void rightClicked();

protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::RightButton)
        {
            emit rightClicked();
        }
        else
        {
            QPushButton::mousePressEvent(event); // вызов стандартного поведения
        }
    }
};

#endif // CELL_H
