#ifndef GAME3_H
#define GAME3_H
#include "winery3.h"

class Game3//Экземпляр игры в узле
{
public:
    int num;
    int players;
    Winery3 *g;
    double ver;
    double q;
    int child_num;
    Game3 **children;
    Game3(int,int,int,int,int,int);
    void Show();

    ~Game3();
    void vShow();
};

#endif // GAME3_H
