#include "winery2.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Winery2::Winery2(int ix, int jx, int play)
{
    if(ix>0)
    {
        i=ix;
    }
    else
    {
        i=5;
    }
    if(jx>0)
    {
        j=jx;
    }
    else
    {
        j=5;
    }
    players=play;
    position = new Element*[i];
    for (int ix = 0; ix < i; ix++)
    {
       position[ix]=new Element[j];
    }
    for (int ix = 0; ix < i; ix++)
    {
        for (int jx = 0; jx < j; jx++)
        {
           position[ix][jx].SetMagic(play);
        }
    }

}

void Winery2::Show()
{
    for (int ix = 0; ix < i; ix++)
        {
            for (int jx = 0; jx < j; jx++)
            {
                position[ix][jx].Show();
                cout <<' ';
            }
            cout <<endl<<endl; // новая строка
        }


}

void Winery2::v_Show()
{
    for (int ix = 0; ix < i; ix++)
        {
            for (int jx = 0; jx < j; jx++)
            {
                position[ix][jx].verShow();
                cout <<' ';
            }
            cout <<endl<<endl; // новая строка
        }
}

void Winery2::Fill(char node[])
{
    float input;

    ifstream in(node);
    for (int ix = 0; ix <i ; ix++)
    {
        for (int jx = 0; jx < j; jx++)
        {
            for(int x = 0; x < position[0][0].pl; x++)
            {
                in>>input;
                position[ix][jx].setEl(x,input);
            }
        }
    }
    in.close();


}
Winery2::~Winery2()
{
    for (int ix=0; ix<i; ix++)
        delete [] position[ix];
    delete [] position;
}

