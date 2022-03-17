#ifndef FIGURE_H
#define FIGURE_H

#include<QColor>
#include<QPainter>
#include <QKeyEvent>

class Figure
{
    QVector<QColor> m_Figure;//[3];
    uint m_x, m_y;
    uint m_W = 20;


public:
    Figure(uint);

    void setPosition(uint, uint);
    QPair<uint,uint> getPosition();
    uint GetRow();
    uint GetCol();
    void rotateColors(Qt::Key);
    void makeRandomColors();
    void paintFigure(QPainter &painter);
    QVector<QColor> getFigure();

};

#endif // FIGURE_H
