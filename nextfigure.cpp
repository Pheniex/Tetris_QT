#include "nextfigure.h"

NextFigure::NextFigure(QWidget *parent) : QWidget(parent)
{

}

void NextFigure::slotChangePattern(Figure *data)
{
    next = data;
    repaint();
}



void NextFigure::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.translate((this->rect().width()/2)-10,0);
    if(next!=nullptr){
        next->paintFigure(painter);
    }
}
