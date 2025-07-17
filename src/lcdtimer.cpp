#include "lcdtimer.h"

#include <iostream>

LCDtimer::LCDtimer(QWidget *parent) : QLCDNumber(parent)
{

}

LCDtimer::LCDtimer(int width, int height, QWidget *parent) : QLCDNumber(parent), m_time(0)
{
    setDigitCount(3);
    setFixedSize(width, height);
    display(m_time);

    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(increaseTimer()));
}

void LCDtimer::start()
{
    reset();
    m_timer->start(1000);
}

void LCDtimer::stop()
{
    m_timer->stop();
}

void LCDtimer::reset()
{
    m_time = 0;
    update();
}

void LCDtimer::update()
{
    display(m_time);
}

void LCDtimer::increaseTimer()
{
    ++m_time;
    update();
}