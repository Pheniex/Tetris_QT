#include "figure.h"
#include<qrandom.h>

Figure::Figure(uint size)
{
    m_W = size;
    m_Figure.resize(3);
}

void Figure::setPosition(uint x, uint y)
{
    m_x = x;
    m_y = y;
}

QPair<uint, uint> Figure::getPosition()
{
    return QPair<uint,uint>(m_x, m_y);
}

uint Figure::GetRow()
{
    return m_y/m_W;
}

uint Figure::GetCol()
{
    return m_x/m_W;
}

void Figure::rotateColors(Qt::Key key)
{
    if(key == Qt::Key_Up){
        std::rotate(m_Figure.begin(), m_Figure.begin()+1, m_Figure.end());
    }
    else if(key == Qt::Key_Down){
        m_Figure.insert(0, m_Figure[2]);
    }
    m_Figure.resize(3);
}

void Figure::makeRandomColors()
{
    QVector<QColor> Color{Qt::red,Qt::green,Qt::blue, Qt::yellow, Qt::cyan};

    for(auto &it : m_Figure){
        it = QColor(Color[rand()%5]);
    }

}

void Figure::paintFigure(QPainter &painter)
{
    //painter.fillRect(W*i, W*j ,W-1,W-1, emptyCell);
    painter.fillRect(m_x, m_y, m_W-1, m_W-1, m_Figure[0]);              //для теста
    painter.fillRect(m_x, m_y+m_W, m_W-1, m_W-1, m_Figure[1]);
    painter.fillRect(m_x, m_y+m_W*2, m_W-1, m_W-1, m_Figure[2]);
}

QVector<QColor> Figure::getFigure()
{
    return m_Figure;
}
