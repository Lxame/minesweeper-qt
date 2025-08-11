#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QIcon>
#include <QMap>
#include <QLCDNumber>
#include <QGridLayout>

#include "cell.h"
#include "lcdmines.h"
#include "lcdtimer.h"

class field : public QWidget
{
    Q_OBJECT
public:
    explicit field(QWidget *parent = nullptr);
    field(quint16 width, quint16 height, quint16 minesCount);

private:
    enum ICON
    {
        def = -1,
        empty = 0,
        one = 1,
        two = 2,
        three = 3,
        four = 4,
        five = 5,
        six = 6,
        seven = 7,
        eight = 8,
        flag = 16,
        red_flag = 32,
        mine = 64,
        mine_boom = 128
    };
    
    quint16 m_width;
    quint16 m_height;
    quint16 m_minesCount;
    quint16 m_flagsPlaced;
    quint16 m_correctedFlagsPlaced;
    std::vector<std::vector<int>> fld;

    QVector<QVector<cell*>> cells;
    QMap<ICON, QIcon> iqons;
    QVBoxLayout* mainLayout;
    QHBoxLayout* controlsLayout;
    QGridLayout* fieldLayout;
    LCDmines* lcdmines;
    LCDtimer* timer;
    QPushButton* smile;

private:
    void initRes();
    bool formField();
    void initField();
    void generateMines();
    void resetCells();
    void disableLayout(QLayout* layout, bool disable = true);

    QGridLayout* initCells();
    quint16 countMinesAroundCell(quint16 x, quint16 y);

    void placeFlag(cell* c, const quint16& x, const quint16& y);
    void removeFlag(cell* c, const quint16& x, const quint16& y);

    void lose(quint16 x, quint16 y);
    void win();

    void updateFieldAfterLose();
    void updateFieldAfterWin();

    void openNearest(quint16 x, quint16 y);    
    void lightNearest(quint16 x, quint16 y, bool show);
    void updateNearestFlagCount(quint16 x, quint16 y, bool increase);

private slots:
    void leftPressed();
    void leftReleased();
    void rightClick();

    void restartGame();
};

#endif // FIELD_H
