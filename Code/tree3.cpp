#include "tree3.h"
#include <iostream>
#include <fstream>
using namespace std;



tree3::tree3(Game3 gg,double q1)
{
  head=new Game3(gg.players,gg.g->i,gg.g->j,gg.g->M,gg.child_num,gg.num);
  for(int i=0;i<gg.child_num;i++)
  {
      head->children[i]=NULL;
  }
  NodeNum=1;
  head->q=q1;
  return;
}

void tree3::push(Game3 **t,int num,Game3 gg,double q,double ver1,bool no)
{

    if((*t)==NULL && no==true) //Если дерева не существует
    {
       (*t)=new Game3(gg.players,gg.g->i,gg.g->j,gg.g->M,gg.child_num,gg.num);
       (*t)->g=gg.g; //Кладем в выделенное место аргумент
        for(int i=0;i<gg.child_num;i++)
        {
            (*t)->children[i]=NULL;
        }
       (*t)->ver=ver1;
       (*t)->q=q;
       (*t)->num=gg.num;
       return;
    }
    else if((*t)==NULL && no==false)
    {
        return;
    }
    if ((*t)->num==num)
    {
        bool yes=true;
        for(int i=0;i<(*t)->child_num;i++)
        {
            if((*t)->children[i]==NULL)
            {
               push(&(*t)->children[i],num,gg,q,ver1,yes);
               break;
            }
        }
    }
    else
    {
        for(int i=0;i<(*t)->child_num;i++)
        {
            push(&(*t)->children[i],num,gg,q,ver1,no);
        }
    }
}
void tree3::sVer(Game3 **t)
{
    float input;
    char n[49]="Resources\\z0ver.txt";
    n[11]=(*t)->num + '0';
    ifstream in(n);

    for (int Mx = 0; Mx < (*t)->g->M; Mx++)
    {
       for (int ix = 0; ix < (*t)->g->i; ix++)
       {
          for (int jx = 0; jx < (*t)->g->j; jx++)
          {
              if((*t)->child_num>0)
              {
                  (*t)->g->position[Mx][ix][jx].SetVer((*t)->child_num);
                  for(int c=0;c<(*t)->child_num;c++)
                  {
                      in>>input;
                      (*t)->g->position[Mx][ix][jx].ver[c]=input;
                  }
              }
              else
              {
                  (*t)->g->position[Mx][ix][jx].SetVer(0);
              }

          }
       }
    }
    for(int i=0;i<(*t)->child_num;i++)
    {
        sVer(&(*t)->children[i]);
    }
}
void tree3::Show(Game3 *t)
{
    if (t==NULL)
    {
        return;
    }
    else
    {

        t->Show();
        for(int i=0;i<t->child_num;i++)
        {
            Show(t->children[i]);
        }
    }
}
tree3::~tree3()
{

}
