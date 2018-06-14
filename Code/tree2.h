#ifndef TREE2_H
#define TREE2_H
#include "game2.h"
#include "winery2.h"

class tree2
{
private:

    int NodeNum;

public:
    Game2 *head;
    tree2(Game2);


    void push(Game2 **t,int,Game2,double,bool);
    void Show(Game2 *t);
    void sVer(Game2 *t);
    ~tree2();
};

#endif // TREE2_H
