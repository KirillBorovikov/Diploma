#include "game2.h"
#include <iostream>

using namespace std;
Game2::Game2(int play,int i,int j,int child,int num1)
{
    players = play;
    num=num1;
    ver=1;
    children = new Game2* [child];
    child_num=child;
    g = new Winery2(i,j,players);
    char ch[46]= "Resources\\z1.txt";
    ch[11]=num1+'0';
    g->Fill(ch);
}

void Game2::vShow()
{
    g->v_Show();
}

void Game2::Show()
{
    g->Show();
}
Game2::~Game2()
{

}

