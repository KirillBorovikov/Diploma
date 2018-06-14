#ifndef GAME2_H
#define GAME2_H
#include "winery2.h"


class Game2//Экземпляр игры в узле
{

public:
    int num;
    int players;
    Winery2 *g;

    double ver;
    Game2 **children;
    int child_num;
    Game2(int,int,int,int,int);
    void vShow();
    void Show();

   ~Game2();

};



#endif // GAME2_H
