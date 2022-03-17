#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QWidget>
#include<QColor>
#include<QPainter>
#include "figure.h"

class NextFigure : public QWidget
{
    Q_OBJECT

   Figure* next = nullptr;

public:
    explicit NextFigure(QWidget *parent = nullptr);

signals:

public slots:
   void slotChangePattern(Figure*);



   // QWidget interface
protected:
   void paintEvent(QPaintEvent *event);
};

#endif // NEXTFIGURE_H
