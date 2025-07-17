#ifndef LCDTIMER_H
#define LCDTIMER_H

#include <QLCDNumber>
#include <QTimer>

class LCDtimer : public QLCDNumber
{
    Q_OBJECT
public:
    explicit LCDtimer(QWidget *parent = nullptr);
    LCDtimer(int width, int height, QWidget *parent = nullptr);

    void start();
    void stop();
    void reset();
    void update();

private:
    QTimer* m_timer;
    ushort m_time;

private slots:
    void increaseTimer();
};

#endif // LCDTIMER_H