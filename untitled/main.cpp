#include <QtGui/QApplication>
#include <iostream>
#include "mainwindow.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush yellowBrush(Qt::yellow);
    QBrush purpleBrush(Qt::magenta);
    QBrush whiteBrush(Qt::white);
    QPen blackpen(Qt::black);

    char test[4] = {'R','B','Y','P'};
    int keep = 2;
    int move = 2;


    int x, y;

    int j;
    for(int i = 0; i < 4; i++)
    {
        switch(test[i])
        {
            case 'R': w.ellipse = w.scene->addEllipse(0+j,0,30,30,blackpen,redBrush);
                      break;
            case 'B': w.ellipse = w.scene->addEllipse(0+j,0,30,30,blackpen,blueBrush);
                      break;
            case 'Y': w.ellipse = w.scene->addEllipse(0+j,0,30,30,blackpen,yellowBrush);
                      break;
            case 'P': w.ellipse = w.scene->addEllipse(0+j,0,30,30,blackpen,purpleBrush);
                      break;
        }
        j+=40;
    }

    if ( keep <= 2 )
    {
        x=0;
        for (int i = 0; i < keep; i++)
        {
            w.ellipse = w.scene->addEllipse(0+x,0,13,13,blackpen,redBrush);
            x+=20;
        }
        if ( move <= 2 )
        {
            x=0;
            for(int i = 0; i < move; i++)
            {
                w.ellipse = w.scene->addEllipse(0+x,15,13,13,blackpen,whiteBrush);
                x+=20;
            }
        }
        else
        {
            x=0;
            w.ellipse = w.scene->addEllipse(0,0,13,13,blackpen,whiteBrush);
            for(int i = 0; i < move-1; i++)
            {
                w.ellipse = w.scene->addEllipse(0+x,15,13,13,blackpen,whiteBrush);
                x+=20;
            }
        }
    }

    if ( keep > 2 )
    {
        w.ellipse = w.scene->addEllipse(0,0,13,13,blackpen,redBrush);
        w.ellipse = w.scene->addEllipse(20,0,13,13,blackpen,redBrush);
        x=0;
        for (int i = 0; i < keep-2; i++)
        {
             w.ellipse = w.scene->addEllipse(0+x,15,13,13,blackpen,redBrush);
             x+=20;
        }
        if (move == 1)
             w.ellipse = w.scene->addEllipse(0,15,13,13,blackpen,whiteBrush);
    }
    return a.exec();
}
