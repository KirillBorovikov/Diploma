#include "tree2.h"
#include <iostream>

using namespace std;



tree2::tree2(Game2 gg)
{
  head=new Game2(gg.players,gg.g->i,gg.g->j,gg.child_num,gg.num);
  for(int i=0;i<gg.child_num;i++)
  {
      head->children[i]=NULL;
  }
  NodeNum=1;

  return;
}




void tree2::push(Game2 **t,int num,Game2 gg,double v,bool no)
{

    if((*t)==NULL && no==true) //Если дерева не существует
    {
       (*t)=new Game2(gg.players,gg.g->i,gg.g->j,gg.child_num,gg.num);
       (*t)->g=gg.g; //Кладем в выделенное место аргумент
       for(int i=0;i<gg.child_num;i++)
       {
           (*t)->children[i]=NULL;
       }
       (*t)->ver=v;
       (*t)->num=gg.num;
       NodeNum+=1;
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
               push(&(*t)->children[i],num,gg,v,yes);
               break;
            }
        }
    }
    else
    {
        for(int i=0;i<(*t)->child_num;i++)
        {
            push(&(*t)->children[i],num,gg,v,no);
        }
    }
}

void tree2::Show(Game2 *t)
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

void tree2::sVer(Game2 *t)
{

    double b;
    for(int i=0;i<t->g->i;i++)
    {
        for(int j=0;j<t->g->j;j++)
        {
            t->g->position[i][j].ver=new double[t->child_num];
            for(int c=0;c<t->child_num;c++)
            {
                t->g->position[i][j].nodes=t->child_num;
                cout<<"Input element probability to node _"<<t->children[c]->num
                   <<"_ from strategy ("<<i+1<<","<<j+1<<") :";
                cin>>b;
                cout<<endl;
                t->g->position[i][j].ver[c]=b;
            }
        }
    }


}


tree2::~tree2()
{

}
