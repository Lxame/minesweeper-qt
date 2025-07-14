#ifndef LCDMINES_H
#define LCDMINES_H

#include <QLCDNumber>

class LCDmines : public QLCDNumber
{
    Q_OBJECT
public:
    explicit LCDmines(QWidget *parent = nullptr);
    LCDmines(ushort mines, int width, int height, QWidget *parent = nullptr);

    void increase();
    void decrease();

private:
    ushort m_minesLeft;
};

#endif // LCDMINES_H
