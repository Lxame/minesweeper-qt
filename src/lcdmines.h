#ifndef LCDMINES_H
#define LCDMINES_H

#include <QLCDNumber>

class LCDmines : public QLCDNumber
{
    Q_OBJECT
public:
    explicit LCDmines(QWidget *parent = nullptr);
    LCDmines(qint8 mines, int width, int height, QWidget *parent = nullptr);

    void increase();
    void decrease();
    void reset(qint8 mines);

private:
    qint8 m_minesLeft;
};

#endif // LCDMINES_H
