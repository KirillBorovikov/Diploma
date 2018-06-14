#include "coop.h"
#include <iostream>

void coop::Show()
{
    for(int i = 0;i<pl_num;i++)
    {
        std::cout<<pl[i]<<' ';
    }
    // std::cout<<std::endl;
}

void coop::mShow()
{
    for(int i = 0;i<node;i++)
    {
        std::cout<<i<<":"<<pay[i]<<' ';
    }
}

coop::coop(int players, int nodes)
{

    pl = new int [players-1];
    pay = new double [nodes];
    pl_num=players;
    node=nodes;
    for (int ix = 0; ix < players; ix++)
    {
       pl[ix] = 0;
    }
    for (int jx = 0; jx < nodes; jx++)
    {
       pay[jx] = 0;
    }
}

int coop::GetNode(int i)
{
    return pay[i];
}

coop::~coop()
{

}

