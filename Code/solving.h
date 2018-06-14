#ifndef SOLVING_H
#define SOLVING_H
#include "coop.h"
#include "tree2.h"
#include "tree3.h"
#include <iostream>
#include <string>
#include <QDesktopWidget>
#include <QStyle>
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
QT_CHARTS_USE_NAMESPACE

class solving
{
public:
    coop *C;
    coop *D_C;
    int players;
    int nodes;
    int number;
    QMainWindow *C_window;

    QMainWindow *DC_window;
    solving(int,int,Game2 **node);
    solving(int,int,Game3 **node);
    void comb(int,int);
    double Fill(Game2 **node, int);
    double Fill3(Game3 **node, int);
    void C_Show(Game2 **node);
    void C_Show3(Game3 **node);
    void DC_Show(Game2 **node);
    void DC_Show3(Game3 **node);

     ~solving();
};

#endif // SOLVING_H
