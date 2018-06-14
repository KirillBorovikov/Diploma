#include "winery3.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Winery3::Winery3(int ix, int jx,int M_num, int play) : Winery2(ix, jx,play)
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
    if(M_num>0)
    {
        M=M_num;
    }
    players=play;
    position = new Element**[M];
    for (int Mx = 0; Mx < M; Mx++)
    {
       position[Mx]=new Element*[i];
       for (int ix = 0; ix < i; ix++)
       {
           position[Mx][ix]=new Element[j];
       }
    }
    for (int Mx = 0; Mx < M; Mx++)
    {
       for (int ix = 0; ix < i; ix++)
       {
          for (int jx = 0; jx < j; jx++)
          {
            position[ix][jx][Mx].SetMagic(play);
          }
        }
     }

}


void Winery3::Show()
{
    cout<<"---------------"<<endl;
    for (int Mx = 0; Mx < M; Mx++)
        {
            for (int ix = 0; ix < i; ix++)
            {
                for (int jx = 0; jx < j; jx++)
                {
                    cout <<"|"<<' ';
                    position[Mx][ix][jx].Show();

                }
                cout<<endl;
            }
            cout<<"----------------"<<endl; // новая строка
        }


}

void Winery3::v_Show()
{
    for (int Mx = 0; Mx < M; Mx++)
        {
            for (int ix = 0; ix < i; ix++)
            {
                for (int jx = 0; jx < j; jx++)
                {
                    position[Mx][ix][jx].verShow();
                    cout <<' ';
                }
                cout <<endl<<endl; // новая строка
            }
    }
}
void Winery3::Fill(char node[])
{
    float input;

    ifstream in(node);
    for (int Mx = 0; Mx < M; Mx++)
    {
       for (int ix = 0; ix < i; ix++)
       {
          for (int jx = 0; jx < j; jx++)
          {
              for(int x = 0; x < players; x++)
              {
                 in>>input;
                 position[Mx][ix][jx].setEl(x,input);
               }
            }
        }
    }
    in.close();

}

Winery3::~Winery3()
{
     for (int ix=0; ix<i; ix++)
     {
        for (int jx=0; jx<j; jx++)
        {
           delete [] position[ix][jx];
        }
        delete [] position[ix];
      }
      delete [] position;
}

