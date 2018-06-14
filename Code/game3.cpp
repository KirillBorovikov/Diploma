#include "game3.h"
#include <iostream>

using namespace std;
Game3::Game3(int play,int i,int j,int M,int child,int num1)
{
    players = play;
    num=num1;
    ver=0;
    child_num=child;
    children = new Game3* [child];
    g = new Winery3(i,j,M,players);
    char ch[47]= "Resources\\zz1.txt";
    ch[12]=num1+'0';
    g->Fill(ch);
    q=1;
}
void Game3::Show()
{
    std::cout<<num<<std::endl;
    g->Show();
}
void Game3::vShow()
{
    g->v_Show();
}
Game3::~Game3()
{

}
