#include "glass.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>



Glass::Glass(QWidget *parent) : QWidget(parent)
{
gameOn = false;

cur = new Figure(W);
next = new Figure(W);
}

Glass::~Glass()
{
    delete cur;
    delete next;
}


void Glass::glassInit(){
    glassArray.resize(m_rows);
    for(auto &it :glassArray){
        it.resize(m_columns);
    }
    s.setHeight(m_rows*W);//m_rows*m_columns*W;
    s.setWidth(m_columns*W);
    //qDebug() << "size " << m_rows;

    this->setFixedSize(s);
}
void Glass::clearGlass(){
    for(auto &it : glassArray){
        it.fill(emptyCell);
    }
}





void Glass::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!gameOn){
        for(int i=0;i<m_columns;++i){
            for(int j=0;j<m_rows;++j){
                painter.fillRect(W*i, W*j ,W-1,W-1, emptyCell);
            }
        }
    }

    else if(gameOn){
        for(int i=0;i<m_columns;++i){
            for(int j=0;j<m_rows;++j){
                painter.fillRect(W*i, W*j ,W-1,W-1, glassArray[j][i]);
            }
        }

        cur->paintFigure(painter);
    }

}


void Glass::slotNewGame()
{
 gameOn = true;
 Score = 0;
 emit setScore(Score);

 idTimer = startTimer(1000);

 clearGlass();

 cur->makeRandomColors();
 cur->setPosition(W*(m_columns/2), 1);


 next->makeRandomColors();
 next->setPosition(0,0); //W*(m_columns/2), 1
 emit signalChangePattern(next);

 this->setFocus();

 repaint();
}

void Glass::slotStart()
{
    glassInit();
}



void Glass::keyPressEvent(QKeyEvent *event)
{
    if(gameOn){
        switch (event->key()) {
        case Qt::Key_Left:
            if(cur->getPosition().first>0){
                if(glassArray[cur->GetRow()+2][cur->GetCol()-1] == emptyCell){
                    cur->setPosition(cur->getPosition().first-W, cur->getPosition().second);
                }
            }
            break;
        case Qt::Key_Right:
            if(cur->getPosition().first<(W*m_columns-W)){
                if(glassArray[cur->GetRow()+2][cur->GetCol()+1] == emptyCell){
                    cur->setPosition(cur->getPosition().first+W, cur->getPosition().second);
                }
            }
            break;
        case Qt::Key_Down:
            cur->rotateColors(Qt::Key_Down);
            break;
        case Qt::Key_Up:
            cur->rotateColors(Qt::Key_Up);
            break;
        case Qt::Key_Space:
            //qDebug() << "olol" << cur->getPosition().first;
            if(glassArray[2][6] == emptyCell){
                goingDown();
            }
            break;
        default:
            QWidget::keyPressEvent(event);
        };

        repaint();
    }
}

void Glass::goingDown()
{
    bool atEndCol = false;
    if((cur->GetRow()+3)!= m_rows && glassArray[cur->GetRow()+3][cur->GetCol()] == emptyCell){
            cur->setPosition(cur->getPosition().first, cur->getPosition().second+W);
    }
    else if((cur->GetRow()+3)== m_rows || glassArray[cur->GetRow()+3][cur->GetCol()] != emptyCell){
            glassArray[cur->GetRow()][cur->GetCol()] = cur->getFigure().at(0);
            glassArray[cur->GetRow()+1][cur->GetCol()] = cur->getFigure().at(1);
            glassArray[cur->GetRow()+2][cur->GetCol()] = cur->getFigure().at(2);
            atEndCol = true;
        }
    if(atEndCol){
        destroyLine();

        Figure *tmp = cur;
        cur = next;
        next = tmp;

        cur->setPosition(W*(m_columns/2), 1);

        next->makeRandomColors();
        next->setPosition(0,0);             //W*(m_columns/2), 1



        emit signalChangePattern(next);
    }
}

void Glass::destroyLine(int curentRow)
{
    for(int i = m_rows - 1; i>0; --i){      //or(int i = m_rows - 1; i>0; --i){
        if((std::equal(glassArray[i].begin() + 1, glassArray[i].end(), glassArray[i].begin()) && glassArray[i][0] == emptyCell)
                && (std::equal(glassArray[i-1].begin() + 1, glassArray[i-1].end(), glassArray[i-1].begin()) && glassArray[i-1][0] == emptyCell)){
            continue;
        }
            int rangeCountStart = 21;
            int rangeCountFinish = 21;
            int inCurRangeCount = 0;
            for (int j = 0; j<m_columns; ++j){
                if(rangeCountFinish != 21){
                    continue;
                }
                if(glassArray[i][j] == glassArray[i][cur->GetCol()]){
                    if (rangeCountStart == 21){
                        rangeCountStart = j;
                    }
                    ++inCurRangeCount;
                }
                if(((rangeCountStart != 21 && rangeCountFinish == 21) && glassArray[i][j] != glassArray[i][cur->GetCol()]) || j == m_columns-1){
                    rangeCountFinish = j;
                    if(inCurRangeCount<3){
                        rangeCountStart = 21;
                        rangeCountFinish = 21;
                        inCurRangeCount = 0;
                    }
                    if(j == m_columns-1){
                        rangeCountFinish = j+1;
                    }
                }
            }
            if(inCurRangeCount>2){
                for (int j = rangeCountStart; j < rangeCountFinish; ++j){
                    if(glassArray[i][j] != emptyCell){
                    ++Score;
                    }

                    glassArray[i][j] = glassArray[i-1][j];
                    glassArray[i-1][j] = emptyCell;
                }

            }

        for(int j = 0; j<m_columns; ++j){
            if(i<m_rows-1){
                if((glassArray[i][j] == glassArray[i+1][j] && glassArray[i][j] == glassArray[i-1][j]) && glassArray[i][j] != emptyCell){
                    int rangeCountStart = 21;
                    int rangeCountFinish = 21;
                    int inCurRangeCount = 0;

                    for(int k = i+1; k >= i-3; --k){
                        if(k<0){
                            continue;
                        }
                        else {
                            if(glassArray[k][j] == glassArray[i][j]){
                                if(rangeCountStart == 21){
                                    rangeCountStart = k;
                                }
                            }
                            if(glassArray[k][j] != glassArray[i][j]  && rangeCountFinish == 21)
                                rangeCountFinish = k;
                        }
                    }
                    for(int k = rangeCountStart; k > rangeCountFinish; --k){
                        glassArray[k][j] = emptyCell;
                        ++Score;
                    }
                    /*
                    glassArray[i-1][j] = glassArray[i-4][j];
                    glassArray[i][j] = glassArray[i-3][j];
                    glassArray[i+1][j] = glassArray[i-2][j];

                    glassArray[i-4][j] = emptyCell;
                    glassArray[i-3][j] = emptyCell;
                    glassArray[i-2][j] = emptyCell;
                    Score += 3; */                            //времяночка
                    }

                }
            }
        for(int j = 0; j<m_columns; ++j){
            if(glassArray[i][j] == emptyCell && glassArray[i-1][j] != emptyCell){
                glassArray[i][j] = glassArray[i-1][j];
                glassArray[i-1][j] = emptyCell;
            }
        }

        repaint();
    }
    //destroyLine();
    if(curentRow >0){
    destroyLine(curentRow-=1);
    }

    emit setScore(Score);
}

void Glass::timerEvent(QTimerEvent *event)
{
    if(glassArray[2][6] != emptyCell){
        killTimer(idTimer);


        QMessageBox::StandardButton GameOver;
        GameOver = QMessageBox::question(this, "Game Over", "Start New Game?");//, QMessageBox::Yes|QMessageBox::No);
        if (GameOver == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            slotNewGame();
          } else {
            qDebug() << "Yes was *not* clicked";
            //this->window()->close();
            this->clearFocus();
            gameOn = false;
          }
    }
    else{
        goingDown();
        repaint();
    }
}
//к этому можно чтонибудь прикрутить   QMessageBox( Icon icon, constQString& title, constQString& text, StandardButtons buttons = NoButton, QWidget * parent = 0, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint)
