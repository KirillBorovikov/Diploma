#ifndef TREE3_H
#define TREE3_H
#include "game3.h"
#include "winery3.h"
#include "element.h"
class tree3
{
private:

    int NodeNum;

public:
    Game3 *head;
    tree3(Game3,double);


    void push(Game3 **t,int,Game3,double,double,bool);
    void Show(Game3 *t);

    ~tree3();
    void sVer(Game3 **t);
};

#endif // TREE3_H
