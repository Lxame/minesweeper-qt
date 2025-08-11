#ifndef CELL_H
#define CELL_H

#include <QPushButton>
#include <QMouseEvent>

class cell : public QPushButton
{
    Q_OBJECT
public:
    explicit cell(QPushButton *parent = nullptr);
    cell(quint16 x, quint16 y, quint16 minesAround, bool isMine);

    quint16 getX()
    {
        return m_x;
    }

    quint16 getY()
    {
        return m_y;
    }

    quint16 minesAround()
    {
        return m_minesAround;
    }

    void setMinesAround(quint16 mines)
    {
        m_minesAround = mines;
    }

    bool isMine()
    {
        return m_isMine;
    }

    void setMine(bool flag)
    {
        m_isMine = flag;
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

    void resetFlagsCount()
    {
        m_flagsAround = 0;
    }

    quint16 getFlagsCount()
    {
        return m_flagsAround;
    }

private:
    status m_current;
    quint16 m_x, m_y;
    quint16 m_minesAround;
    quint16 m_flagsAround;
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
