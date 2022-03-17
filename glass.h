#ifndef GLASS_H
#define GLASS_H

#include <QWidget>
#include <QVariant>
#include <QTimerEvent>
#include "figure.h"

class Glass : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint columns READ columns WRITE setColumns)

    const uint W = 20;

    uint timerInterval;

    uint m_rows;
    uint m_columns;

    QSize s;

    bool gameOn;
    uint score;

    QColor emptyCell = QColor(150,150,150);
    QVector < QVector < QColor > > glassArray;

    Figure *cur;
    Figure *next;

    int Score;

    int idTimer;
    void timerEvent(QTimerEvent*event);

public:
    explicit Glass(QWidget *parent = nullptr);
    ~Glass();

    uint rows() const
    {
        return m_rows;
    }

    uint columns() const
    {
        return m_columns;
    }

    void glassInit();
    void clearGlass();
    void goingDown();
    void destroyLine(int curentRow = 19);

public slots:
    void setRows(uint rows)
    {
        m_rows = rows;
    }

    void setColumns(uint columns)
    {
        m_columns = columns;
    }
    void slotNewGame();
    void slotStart();

signals:
    void signalChangePattern(Figure*);
    void setScore(int);

        // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // GLASS_H
