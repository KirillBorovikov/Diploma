#include "solving.h"
QT_CHARTS_USE_NAMESPACE


solving::solving(int pl, int n,Game2 **node)
{
    players = pl;
    nodes=n;
    int num = (pow(2,pl)-1);
    number=num;
    C_window = new QMainWindow[nodes];
    DC_window = new QMainWindow[nodes];

    C = (coop*)operator new( sizeof(coop) *num);
    for(int i=0; i<num; ++i )
    {
      new(&C[i]) coop(pl,n);
    }
    D_C = (coop*)operator new( sizeof(coop) *num);
    for(int i=0; i<num; ++i )
    {
      new(&D_C[i]) coop(pl,n);
    }
    comb(3,2);

    for(int i=0;i<num;++i)
    {
        Fill(&(*node),i);
    }
    C_Show(&(*node));
    DC_Show(&(*node));

}

solving::solving(int pl, int n, Game3 **node)
{
    players = pl;
    nodes=n;
    int num = (pow(2,pl)-1);
    number=num;
    C_window = new QMainWindow[nodes];
    DC_window = new QMainWindow[nodes];
    C = (coop*)operator new( sizeof(coop) *num);
    for(int i=0; i<num; ++i )
    {
      new(&C[i]) coop(pl,n);
    }
    D_C = (coop*)operator new( sizeof(coop) *num);
    for(int i=0; i<num; ++i )
    {
      new(&D_C[i]) coop(pl,n);
    }
    comb(4,3);

    for(int i=0;i<num;++i)
    {
        Fill3(&(*node),i);
    }

    C_Show3(&(*node));
    DC_Show3(&(*node));

}

void solving::comb(int N, int K)
{
    std::string bitmask(K, 1);
    bitmask.resize(N, 0);
    int ix=0;
    int j=0;
    for(int i=0;i<players;++i)
    {
      C[i].pl[players-1]=i+1;
      D_C[i].pl[players-1]=i+1;
      ix++;
    }
    if(players>2)
    {
    do {

        for (int i = 0; i < N; ++i)
        {
           if (bitmask[i])
           {
              std::cout << i<<" ";
              C[ix].pl[j]=i;
              D_C[ix].pl[j]=i;
              j++;
           }
        }
        std::cout << std::endl;
        ix++;
        j=0;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }
    else
    {
        for(int i=0;i<2;++i)
        {
          C[ix].pl[i]=i+1;
          D_C[ix].pl[i]=i+1;
        }
    }
}

double solving::Fill(Game2 **node,int pos)
{

    if ((*node)==NULL)
    {
       return 0;
    }
    else
    {

        double payoff[(*node)->g->i];
        payoff[0]=0;
        double check=0;
        double check1=0,checkD1=0,checkD2=0;
        double dop=0;

        if(pos==0)
        {
            for(int i=0;i<(*node)->child_num/2;i++)
            {
                check=check+Fill(&(*node)->children[i],pos);
            }
            for(int j=(*node)->child_num/2;j<(*node)->child_num;j++)
            {
                check1=check1+Fill(&(*node)->children[j],pos);
            }
            checkD1=check;
            checkD2=check1;

            if(((*node)->g->i==1) && ((*node)->g->j==1))
            {
                check=(*node)->g->position[0][0].el[pos];

                checkD1=check-checkD1;
                D_C[pos].pay[(*node)->num]=checkD1;
                //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------

                C[pos].pay[(*node)->num]=check;
                //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                return (*node)->ver*check;
            }
            else
            {
                for (int ix = 0; ix < (*node)->g->i; ix++)
                {
                  for (int jx = 1; jx < (*node)->g->j; jx++)
                  {
                      payoff[ix]=min((*node)->g->position[ix][jx-1].el[pos],
                              (*node)->g->position[ix][jx].el[pos]);
                      //std::cout<<" "<<(*node)->num<<":"<<payoff[ix];//--------------ПРОВЕРКА----------------

                  }
                  if(ix>0)
                  {
                      dop=max(payoff[ix],payoff[ix-1]);
                      //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                  }
                }
                if(check>check1)
                {
                 check=dop+check;

                 checkD1=check-checkD1;
                 D_C[pos].pay[(*node)->num]=checkD1;
                 //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------

                 //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                 C[pos].pay[(*node)->num]=check;

                 return (*node)->ver*check;
                }
                else
                {
                 check1=dop+check1;

                 checkD2=check1-checkD2;
                 D_C[pos].pay[(*node)->num]=checkD2;
                 //std::cout<<" "<<(*node)->num<<":"<<checkD2;//--------------ПРОВЕРКА----------------

                 //std::cout<<" "<<(*node)->num<<":"<<check1;//--------------ПРОВЕРКА----------------
                 C[pos].pay[(*node)->num]=check1;

                 return (*node)->ver*check1;
                }

            }

        }
        else if(pos==1)
        {
            for(int i=0;i<(*node)->child_num/2;i++)
            {
                check=check+Fill(&(*node)->children[i],pos);
            }
            for(int j=(*node)->child_num/2;j<(*node)->child_num;j++)
            {
                check1=check1+Fill(&(*node)->children[j],pos);
            }
            checkD1=check;
            checkD2=check1;
            if(((*node)->g->i==1) && ((*node)->g->j==1))
            {
                check=(*node)->g->position[0][0].el[pos];

                checkD1=check-checkD1;
                D_C[pos].pay[(*node)->num]=checkD1;
                //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------

                C[pos].pay[(*node)->num]=check;
                //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                return (*node)->ver*check;
            }
            else
            {
                for (int ix = 1; ix < (*node)->g->i; ix++)
                {
                  for (int jx = 0; jx < (*node)->g->j; jx++)
                  {
                      payoff[jx]=min((*node)->g->position[ix-1][jx].el[pos],
                              (*node)->g->position[ix][jx].el[pos]);

                  }
                  dop=max(payoff[ix],payoff[ix-1]);
                }
                if(check>check1)
                {
                 check=dop+check;

                 checkD1=check-checkD1;
                 D_C[pos].pay[(*node)->num]=checkD1;
                 //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------

                 //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                 C[pos].pay[(*node)->num]=check;
                 return (*node)->ver*check;
                }
                else
                {
                 check1=dop+check1;

                 checkD2=check1-checkD2;
                 D_C[pos].pay[(*node)->num]=checkD2;
                 //std::cout<<" "<<(*node)->num<<":"<<checkD2;//--------------ПРОВЕРКА----------------

                 //std::cout<<" "<<(*node)->num<<":"<<check1;//--------------ПРОВЕРКА---------------
                 C[pos].pay[(*node)->num]=check1;
                 return (*node)->ver*check1;
                }
            }

        }
        else
        {
            for(int i=0;i<(*node)->child_num/2;i++)
            {
                check=check+Fill(&(*node)->children[i],pos);
            }
            for(int j=(*node)->child_num/2;j<(*node)->child_num;j++)
            {
                check1=check1+Fill(&(*node)->children[j],pos);
            }
         checkD1=check;
         checkD2=check1;

         if(((*node)->g->i==1) && ((*node)->g->j==1))
         {
             double dd=0;
             for (int qx = 0; qx <(*node)->g->position[0][0].pl; qx++)
             {
                dd=dd+(*node)->g->position[0][0].el[qx];
             }
             check=dd;

             checkD1=check-checkD1;
             D_C[pos].pay[(*node)->num]=checkD1;
             //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------

             C[pos].pay[(*node)->num]=check;
             //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
             return (*node)->ver*check;
         }
         else
         {
             double dd=0;
             for (int ix = 0; ix < (*node)->g->i; ix++)
             {
              for (int jx = 0; jx < (*node)->g->j; jx++)
              {
                  for (int qx = 0; qx <(*node)->g->position[ix][jx].pl; qx++)
                  {
                     dd=dd+(*node)->g->position[ix][jx].el[qx];
                  }
                  if(dd>dop)
                  {
                    dop=dd;
                    //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                  }
                  dd=0;
              }
             }
             if(check>check1)
             {
              check=dop+check;

              checkD1=check-checkD1;
              D_C[pos].pay[(*node)->num]=checkD1;
              //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------

              //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
              C[pos].pay[(*node)->num]=check;
              return (*node)->ver*check;
             }
             else
             {
              check1=dop+check1;

              checkD2=check1-checkD2;
              D_C[pos].pay[(*node)->num]=checkD2;
              //std::cout<<" "<<(*node)->num<<":"<<checkD2;//--------------ПРОВЕРКА----------------

              //std::cout<<" "<<(*node)->num<<":"<<check1;//--------------ПРОВЕРКА----------------
              C[pos].pay[(*node)->num]=check1;
              return (*node)->ver*check1;
             }
           }

       }
    }

}

double solving::Fill3(Game3 **node, int pos)
{

    if ((*node)==NULL)
    {
       return 0;
    }
    else
    {


        double comp=0,comp1=0,comp3=0;
        double check=0;
        double checkD1=0;
        double dop=0;
        switch(pos)
        {
            case 0:
            {
                double payoff[(*node)->g->i];
                for(int i=0;i<(*node)->child_num;i++)
                {
                    check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
                }
                checkD1=check;


                for (int ix = 0; ix < (*node)->g->i; ix++)
                {
                  for (int Mx = 0; Mx < (*node)->g->M; Mx++)
                  {
                      for (int jx = 1; jx < (*node)->g->j; jx++)
                      {
                         for(int i=0;i<(*node)->child_num;i++)
                         {
                             comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                     position[Mx][ix][jx].ver[i]);

                             comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                     position[Mx][ix][jx-1].ver[i]);

                         }
                         comp3=min((*node)->g->position[Mx][ix][jx].el[pos]+comp,
                                        (*node)->g->position[Mx][ix][jx-1].el[pos]+comp1);
                         comp=0;
                         comp1=0;
                      }
                      if(Mx==0)
                      {
                          payoff[ix]=comp3;

                      }
                      else if(comp3<payoff[ix])
                      {
                          payoff[ix]=comp3;
                      }
                      //std::cout<<" "<<(*node)->num<<":"<<payoff[ix];//--------------ПРОВЕРКА----------------

                  }
                  if(ix>0)
                  {
                      dop=max(payoff[ix],payoff[ix-1]);

                      //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                  }
                }
                 check=dop;
                 //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                 C[pos].pay[(*node)->num]=check;

                 checkD1=check;
                 for(int i=0;i<(*node)->child_num;i++)
                 {
                    checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
                 }
                 D_C[pos].pay[(*node)->num]=checkD1;
                 //std::cout<<" "<<(*node)->num<<":"<<checkD1;//--------------ПРОВЕРКА----------------
                 return check;


            }
            case 1:
            {
            double payoff[(*node)->g->j];
            for(int i=0;i<(*node)->child_num;i++)
            {
                check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
            }
            checkD1=check;


            for (int jx = 0; jx < (*node)->g->j; jx++)
                {
                  for (int Mx = 0; Mx < (*node)->g->M; Mx++)
                  {
                      for (int ix = 1; ix < (*node)->g->i; ix++)
                      {
                          for(int i=0;i<(*node)->child_num;i++)
                          {
                              comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                      position[Mx][ix][jx].ver[i]);

                              comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                      position[Mx][ix-1][jx].ver[i]);

                          }
                          comp3=min((*node)->g->position[Mx][ix][jx].el[pos]+comp,
                                         (*node)->g->position[Mx][ix-1][jx].el[pos]+comp1);
                          comp=0;
                          comp1=0;

                      }
                      if(Mx==0)
                      {
                          payoff[jx]=comp3;

                      }
                      else if(comp3<payoff[jx])
                      {
                          payoff[jx]=comp3;
                      }
                      //std::cout<<" "<<(*node)->num<<":"<<payoff[jx];//--------------ПРОВЕРКА----------------

                  }
                  if(jx>0)
                  {
                      dop=max(payoff[jx],payoff[jx-1]);
                      //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                  }
                }
               check=dop;

               //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
               C[pos].pay[(*node)->num]=check;

               checkD1=check;
               for(int i=0;i<(*node)->child_num;i++)
               {
                  checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
               }
               D_C[pos].pay[(*node)->num]=checkD1;
               return check;
            }
            case 2:
            {
            double payoff[(*node)->g->M];
            for(int i=0;i<(*node)->child_num;i++)
            {
                check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
            }
            checkD1=check;

            for (int Mx = 0; Mx < (*node)->g->M; Mx++)
                {
                  for (int ix = 0; ix < (*node)->g->i; ix++)
                  {
                      for (int jx = 1; jx < (*node)->g->j; jx++)
                      {
                          for(int i=0;i<(*node)->child_num;i++)
                          {
                              comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                      position[Mx][ix][jx].ver[i]);

                              comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                      position[Mx][ix][jx-1].ver[i]);

                          }
                          comp3=min((*node)->g->position[Mx][ix][jx].el[pos]+comp,
                                         (*node)->g->position[Mx][ix][jx-1].el[pos]+comp1);
                          comp=0;
                          comp1=0;
                      }
                      if(ix==0)
                      {
                          payoff[Mx]=comp3;
                      }
                      else if(comp3<payoff[Mx])
                      {
                          payoff[Mx]=comp3;
                      }
                      //std::cout<<" "<<(*node)->num<<":"<<payoff[Mx];//--------------ПРОВЕРКА----------------

                  }
                  if(Mx>0)
                  {
                      dop=max(payoff[Mx],payoff[Mx-1]);
                      //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                  }
                }
                check=dop;
                //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                C[pos].pay[(*node)->num]=check;

                checkD1=check;
                for(int i=0;i<(*node)->child_num;i++)
                {
                   checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
                }
                D_C[pos].pay[(*node)->num]=checkD1;
                return check;
            }
            case 3:
            {
            double payoff[(*node)->g->i];
            for(int i=0;i<(*node)->child_num;i++)
            {
                check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
            }
            checkD1=check;
            double dd=0,dd1=0;
            for (int ix = 0; ix < (*node)->g->i; ix++)
            {
                for (int jx = 0; jx < (*node)->g->j; jx++)
                {
                    for (int Mx = 1; Mx < (*node)->g->M; Mx++)
                    {
                      for (int qx = 0; qx <2; qx++)
                      {
                         dd=dd+(*node)->g->position[Mx][ix][jx].el[qx];
                         dd1=dd1+(*node)->g->position[Mx-1][ix][jx].el[qx];
                      }
                      for(int i=0;i<(*node)->child_num;i++)
                      {
                          comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                  position[Mx][ix][jx].ver[i]);

                          comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                  position[Mx-1][ix][jx].ver[i]);

                      }
                      comp3=min(dd+comp,dd1+comp1);
                      comp=0;
                      comp1=0;

                      dd=0;
                      dd1=0;
                      }
                       if(jx==0)
                       {
                         payoff[ix]=comp3;
                       }
                       else if(comp3>payoff[ix])
                       {
                         payoff[ix]=comp3;
                       }
                       //std::cout<<" "<<(*node)->num<<":"<<payoff[ix];//--------------ПРОВЕРКА----------------
                    }
                    if(ix>0)
                    {
                        dop=max(payoff[ix],payoff[ix-1]);
                        //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                    }
                }
                check=dop;
                //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                C[pos].pay[(*node)->num]=check;

                checkD1=check;
                for(int i=0;i<(*node)->child_num;i++)
                {
                   checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
                }
                D_C[pos].pay[(*node)->num]=checkD1;
                return check;
            }
            case 4:
            {

                double payoff[(*node)->g->i];
                for(int i=0;i<(*node)->child_num;i++)
                {
                    check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
                }

                checkD1=check;
                double dd=0,dd1=0;
                for (int ix = 0; ix < (*node)->g->i; ix++)
                {
                 for (int Mx = 0; Mx < (*node)->g->M; Mx++)
                 {
                  for (int jx = 1; jx < (*node)->g->j; jx++)
                  {
                      for (int qx = 2; qx>0; qx--)
                      {
                         dd=dd+(*node)->g->position[Mx][ix][jx].el[C[pos].pl[qx]-1];
                         dd1=dd1+(*node)->g->position[Mx][ix][jx-1].el[C[pos].pl[qx]-1];

                      }

                      for(int i=0;i<(*node)->child_num;i++)
                      {
                          comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                  position[Mx][ix][jx].ver[i]);



                          comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                  position[Mx][ix][jx-1].ver[i]);



                      }
                      comp3=min(dd+comp,dd1+comp1);


                      comp=0;
                      comp1=0;
                      dd=0;
                      dd1=0;
                  }
                  if(Mx==0)
                  {
                    payoff[ix]=comp3;
                  }
                  else if(comp3>payoff[ix])
                  {
                    payoff[ix]=comp3;
                  }
               }
                //std::cout<<" "<<(*node)->num<<":"<<payoff[ix];//--------------ПРОВЕРКА----------------
               if(ix>0)
               {
                  dop=max(payoff[ix],payoff[ix-1]);
                  //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
               }

            }
            check=dop;

            checkD1=check-checkD1;
            //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
            C[pos].pay[(*node)->num]=check;

            checkD1=check;
            for(int i=0;i<(*node)->child_num;i++)
            {
               checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
            }
            D_C[pos].pay[(*node)->num]=checkD1;
            return check;

            }
            case 5:
            {
            double payoff[(*node)->g->M];
            for(int i=0;i<(*node)->child_num;i++)
            {
                check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
            }
            checkD1=check;

            double dd=0,dd1=0;
            for (int Mx = 0; Mx < (*node)->g->M; Mx++)
            {
               for (int jx = 0; jx < (*node)->g->j; jx++)
               {
                  for (int ix = 1; ix < (*node)->g->i; ix++)
                  {
                      for (int qx = 1; qx <3; qx++)
                      {

                         dd=dd+(*node)->g->position[Mx][ix][jx].el[qx];
                         dd1=dd1+(*node)->g->position[Mx][ix-1][jx].el[qx];

                      }
                      for(int i=0;i<(*node)->child_num;i++)
                      {
                          comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                  position[Mx][ix][jx].ver[i]);

                          comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                  position[Mx][ix-1][jx].ver[i]);


                      }
                      comp3=min(dd+comp,dd1+comp1);

                      dd=0;
                      dd1=0;
                      comp=0;
                      comp1=0;
                  }
                   if(jx==0)
                   {
                     payoff[Mx]=comp3;
                   }
                   else if(comp3>payoff[Mx])
                   {
                     payoff[Mx]=comp3;
                   }
                   //std::cout<<" "<<(*node)->num<<":"<<payoff[ix];//--------------ПРОВЕРКА----------------
                }
                if(Mx>0)
                {
                    dop=max(payoff[Mx],payoff[Mx-1]);
                    //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                }
            }

             check=dop;
             //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
             C[pos].pay[(*node)->num]=check;

             checkD1=check;
             for(int i=0;i<(*node)->child_num;i++)
             {
                checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
             }
             D_C[pos].pay[(*node)->num]=checkD1;

             return check;
           }
            case 6:
            {
            double payoff[(*node)->g->M];
            for(int i=0;i<(*node)->child_num;i++)
            {
                check=check+(*node)->q*Fill3(&(*node)->children[i],pos);
            }

            checkD1=check;

            double dd=0,dd1=0;
            for (int Mx = 0; Mx < (*node)->g->M; Mx++)
                {
                  for (int ix = 0; ix < (*node)->g->i; ix++)
                  {
                      for (int jx = 1; jx < (*node)->g->j; jx++)
                      {
                          for (int qx = 0; qx <3; qx++)
                          {
                             dd=dd+(*node)->g->position[Mx][ix][jx].el[qx];
                             dd1=dd1+(*node)->g->position[Mx][ix][jx-1].el[qx];

                          }
                          for(int i=0;i<(*node)->child_num;i++)
                          {
                              comp=comp+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                      position[Mx][ix][jx].ver[i]);

                              comp1=comp1+(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->g->
                                      position[Mx][ix][jx-1].ver[i]);


                          }
                          comp3=max(dd+comp,dd1+comp1);

                          dd=0;
                          dd1=0;
                          comp=0;
                          comp1=0;
                      }
                      if(ix==0)
                      {
                          payoff[Mx]=comp3;

                      }
                      else if(comp3>payoff[Mx])
                      {
                          payoff[Mx]=comp3;
                      }
                      //std::cout<<" "<<(*node)->num<<":"<<payoff[jx];//--------------ПРОВЕРКА----------------

                  }
                  if(Mx>0)
                  {
                      dop=max(payoff[Mx],payoff[Mx-1]);
                      //std::cout<<" "<<(*node)->num<<":"<<dop;//--------------ПРОВЕРКА----------------
                  }
                }
                check=dop;
                //std::cout<<" "<<(*node)->num<<":"<<check;//--------------ПРОВЕРКА----------------
                C[pos].pay[(*node)->num]=check;

                checkD1=check;
                for(int i=0;i<(*node)->child_num;i++)
                {
                   checkD1=checkD1-(*node)->q*(C[pos].pay[(*node)->children[i]->num]*(*node)->children[i]->ver);
                }
                D_C[pos].pay[(*node)->num]=checkD1;
                return check;


            }
        }

    }

}

void solving::C_Show(Game2 **node)
{
    if ((*node)==NULL)
    {
       return;
    }
    else
    {
                QLineSeries *series0 = new QLineSeries();
                QLineSeries *series1 = new QLineSeries();
                double i=0;
                double x=0,y=0;
                *series0 << QPointF(C[0].pay[(*node)->num]+i, C[2].pay[(*node)->num]-(C[0].pay[(*node)->num]+i));
                *series1 <<  QPointF(C[0].pay[(*node)->num]+i, C[2].pay[(*node)->num]-(C[0].pay[(*node)->num]+i));
                do
                {
                  i+=0.5;
                  *series0 << QPointF(C[0].pay[(*node)->num]+i,C[2].pay[(*node)->num]-(C[0].pay[(*node)->num]+i));
                  y=C[1].pay[(*node)->num]+i;
                  x=C[0].pay[(*node)->num]+i;
                  *series1 << QPointF(C[0].pay[(*node)->num]+i,C[2].pay[(*node)->num]-(C[0].pay[(*node)->num]+i));
                }while(i<(C[2].pay[(*node)->num]-C[1].pay[(*node)->num])-C[0].pay[(*node)->num]);

                QAreaSeries *series = new QAreaSeries(series0, series1);
                QString q;
                q.setNum((*node)->num);
                series->setName(q);
                QPen pen(0x059605);
                pen.setWidth(2);
                series->setPen(pen);

                QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
                gradient.setColorAt(0.0, 0x3cc63c);
                gradient.setColorAt(1.0, 0x26f626);
                gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                series->setBrush(gradient);

                QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("C-core");
                chart->createDefaultAxes();

                QValueAxis *axisX = new QValueAxis;
                axisX->setRange(C[0].pay[(*node)->num], x);
                axisX->setTickCount(10);
                axisX->setLabelFormat("%.2f");
                QValueAxis *axisY = new QValueAxis;
                axisY->setRange(C[1].pay[(*node)->num], y);
                axisY->setTickCount(10);
                axisY->setLabelFormat("%.2f");

                QChartView *chartView = new QChartView(chart);
                chartView->chart()->setAxisX(axisX, series);
                chartView->chart()->setAxisY(axisY, series);
                chartView->setRenderHint(QPainter::Antialiasing);


                C_window[(*node)->num].setCentralWidget(chartView);
                QDesktopWidget desktop;
                QRect rect = desktop.availableGeometry(desktop.primaryScreen());
                QPoint center = rect.center();
                int x1 = center.x() - (C_window[(*node)->num].width()/2);
                int y1 = center.y() - (C_window[(*node)->num].height()/2);
                center.setX(x1);
                center.setY(y1);
                C_window[(*node)->num].resize(700, 600);
                //C_window[(*node)->num].show();

                for(int i=0;i<(*node)->child_num;i++)
                {
                    C_Show(&(*node)->children[i]);
                }


        }


}

void solving::C_Show3(Game3 **node)
{
    if ((*node)==NULL)
    {
       return;
    }
    else
    {
        QLineSeries *series0 = new QLineSeries();
        QLineSeries *series1 = new QLineSeries();
        double temp=0;
        double ang_1[2],ang_2[3],ang_3[2];

        ang_1[0]=C[6].pay[(*node)->num]-C[1].pay[(*node)->num]-C[2].pay[(*node)->num];
        ang_1[1]=C[2].pay[(*node)->num];
        ang_2[0]=C[0].pay[(*node)->num];
        ang_2[1]=C[2].pay[(*node)->num];
        ang_3[0]=C[0].pay[(*node)->num];
        ang_3[1]=C[6].pay[(*node)->num]-C[0].pay[(*node)->num]-C[1].pay[(*node)->num];

        double right[2],left[2],up[2];
        if(ang_3[0]>ang_1[0])
        {
                right[0]=ang_3[0];
                right[1]=ang_3[1];
        }
        else
        {
                right[0]=ang_1[0];
                right[1]=ang_1[1];
        }
        if(right[0]<ang_2[0])
        {
                right[0]=ang_2[0];
                right[1]=ang_2[1];
        }
        if(ang_3[1]>ang_1[1])
        {
           up[0]=ang_3[0];
           up[1]=ang_3[1];
        }
        else
        {
            up[0]=ang_1[0];
            up[1]=ang_1[1];
        }
        if(up[1]<ang_2[1])
        {
            up[0]=ang_2[0];
            up[1]=ang_2[1];
        }
        left[0]=up[0];
        left[1]=right[1];

        double dopang[2],dopang2[2];
        dopang[0]=up[0];
        dopang[1]=up[1];


        ang_2[0]=C[0].pay[(*node)->num];
        ang_2[1]=C[6].pay[(*node)->num]-C[0].pay[(*node)->num]-C[2].pay[(*node)->num];
        ang_2[2]=C[2].pay[(*node)->num];

        double left2[2],up2[2];
        temp=ang_2[1]-C[4].pay[(*node)->num];
        left2[0]=left[0]+temp;
        left2[1]=left[1];
        up2[1]=left[1]+temp;
        up2[0]=up[0];
        up[1]=C[3].pay[(*node)->num];

        double i=0;
        do
        {
           dopang[0]+=i;
           dopang[1]-=i;
           i+=0.1;
        }while(dopang[1]>C[3].pay[(*node)->num]);
        dopang[1]=C[3].pay[(*node)->num];

        dopang2[0]=dopang[0];
        dopang2[1]=dopang[1];
        while(dopang2[0]<C[5].pay[(*node)->num])
        {
           i+=0.1;
           dopang2[0]+=i;
           dopang2[1]-=i;

        }
        dopang2[0]=C[5].pay[(*node)->num];
        if(dopang2[1]<left2[1])
        {
            dopang2[1]=left2[1];
        }




        if(left2[0]<C[5].pay[(*node)->num])
        {
            double dopang3[2];
            dopang3[0]=C[5].pay[(*node)->num];
            dopang3[1]=left2[1];
            *series0 << QPointF(up[0],up[1])<<QPointF(dopang[0],dopang[1])<<QPointF(dopang2[0],dopang2[1])
                    <<QPointF(C[5].pay[(*node)->num],up[1]);
            *series1 << QPointF(up2[0],up2[1])<<QPointF(left2[0],left2[1])<<QPointF(dopang3[0],dopang3[1]);
        }
        else
        {
            *series0 << QPointF(up[0],up[1]) <<QPointF(dopang[0],dopang[1])<<QPointF(dopang2[0],dopang2[1])
                    <<QPointF(C[5].pay[(*node)->num],up[1]);
            *series1 << QPointF(up2[0],up2[1])<<QPointF(left2[0],left2[1]);
        }


        QAreaSeries *series = new QAreaSeries(series0, series1);
        QString q;
        q.setNum((*node)->num);
        series->setName(q);
        QPen pen(0x059605);
        pen.setWidth(2);
        series->setPen(pen);

        QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
        gradient.setColorAt(0.0, 0x3cc63c);
        gradient.setColorAt(1.0, 0x26f626);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        series->setBrush(gradient);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("C-core");
        chart->createDefaultAxes();

        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(left[0], C[5].pay[(*node)->num]);
        axisX->setTickCount(10);
        axisX->setLabelFormat("%.2f");
        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(left[1], up[1]);
        axisY->setTickCount(10);
        axisY->setLabelFormat("%.2f");

        QChartView *chartView = new QChartView(chart);
        chartView->chart()->setAxisX(axisX, series);
        chartView->chart()->setAxisY(axisY, series);
        chartView->setRenderHint(QPainter::Antialiasing);

        QDesktopWidget desktop;
        C_window[(*node)->num].setCentralWidget(chartView);
        QRect rect = desktop.availableGeometry(desktop.primaryScreen());
        QPoint center = rect.center();
        int x1 = center.x() - (C_window[(*node)->num].width()/2);
        int y1 = center.y() - (C_window[(*node)->num].height()/2);
        center.setX(x1);
        center.setY(y1);
        C_window[(*node)->num].resize(700, 600);
        //C_window[(*node)->num].show();


        for(int i=0;i<(*node)->child_num;i++)
        {
            C_Show3(&(*node)->children[i]);
        }

    }
}

void solving::DC_Show(Game2 **node)
{
    if ((*node)==NULL)
    {
       return;
    }
    else
    {
        switch(players)
        {
            case 2:
            {
                QLineSeries *series0 = new QLineSeries();
                QLineSeries *series1 = new QLineSeries();
                double i=0;
                double x=0,y=0;
                *series0 << QPointF(D_C[0].pay[(*node)->num]+i,
                        D_C[2].pay[(*node)->num]-(D_C[0].pay[(*node)->num]+i));
                *series1 << QPointF(D_C[0].pay[(*node)->num]+i,
                        D_C[2].pay[(*node)->num]-(D_C[0].pay[(*node)->num]+i));
                do
                {
                  i+=0.5;
                  *series0 << QPointF(D_C[0].pay[(*node)->num]+i,
                          D_C[2].pay[(*node)->num]-(D_C[0].pay[(*node)->num]+i));
                  y=D_C[1].pay[(*node)->num]+i;
                  x=D_C[0].pay[(*node)->num]+i;
                  *series1 << QPointF(D_C[0].pay[(*node)->num]+i,
                          D_C[2].pay[(*node)->num]-(D_C[0].pay[(*node)->num]+i));
                }while(i<(D_C[2].pay[(*node)->num]-D_C[1].pay[(*node)->num])-D_C[0].pay[(*node)->num]);

                QAreaSeries *series = new QAreaSeries(series0, series1);
                QString q;
                q.setNum((*node)->num);
                series->setName(q);
                QPen pen(0xb80000);
                pen.setWidth(2);
                series->setPen(pen);

                QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
                gradient.setColorAt(0.0, 0xff2006);
                gradient.setColorAt(1.0, 0xfb1a00);
                gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
                series->setBrush(gradient);

                QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("Delta C-core");
                chart->createDefaultAxes();

                QValueAxis *axisX = new QValueAxis;
                axisX->setRange(D_C[0].pay[(*node)->num], x);
                axisX->setTickCount(10);
                axisX->setLabelFormat("%.2f");
                QValueAxis *axisY = new QValueAxis;
                axisY->setRange(D_C[1].pay[(*node)->num], y);
                axisY->setTickCount(10);
                axisY->setLabelFormat("%.2f");

                QChartView *chartView = new QChartView(chart);
                chartView->chart()->setAxisX(axisX, series);
                chartView->chart()->setAxisY(axisY, series);
                chartView->setRenderHint(QPainter::Antialiasing);

                DC_window[(*node)->num].setCentralWidget(chartView);
                QDesktopWidget desktop;
                QRect rect = desktop.availableGeometry(desktop.primaryScreen());
                QPoint center = rect.center();
                int x1 = center.x() - (DC_window[(*node)->num].width()/2);
                int y1 = center.y() - (DC_window[(*node)->num].height()/2);
                center.setX(x1);
                center.setY(y1);
                DC_window[(*node)->num].resize(700, 600);
                //DC_window[(*node)->num].show();
                for(int i=0;i<(*node)->child_num;i++)
                {
                    DC_Show(&(*node)->children[i]);
                }
            }
        }

    }
}

void solving::DC_Show3(Game3 **node)
{
    if ((*node)==NULL)
    {
       return;
    }
    else
    {
        QLineSeries *series0 = new QLineSeries();
        QLineSeries *series1 = new QLineSeries();
        double temp=0;
        double ang_1[2],ang_2[3],ang_3[2];

        ang_1[0]=D_C[6].pay[(*node)->num]-D_C[1].pay[(*node)->num]-D_C[2].pay[(*node)->num];
        ang_1[1]=D_C[2].pay[(*node)->num];
        ang_2[0]=D_C[0].pay[(*node)->num];
        ang_2[1]=D_C[2].pay[(*node)->num];
        ang_3[0]=D_C[0].pay[(*node)->num];
        ang_3[1]=D_C[6].pay[(*node)->num]-D_C[0].pay[(*node)->num]-D_C[1].pay[(*node)->num];

        double right[2],left[2],up[2];
        if(ang_3[0]>ang_1[0])
        {
                right[0]=ang_3[0];
                right[1]=ang_3[1];
        }
        else
        {
                right[0]=ang_1[0];
                right[1]=ang_1[1];
        }
        if(right[0]<ang_2[0])
        {
                right[0]=ang_2[0];
                right[1]=ang_2[1];
        }
        if(ang_3[1]>ang_1[1])
        {
           up[0]=ang_3[0];
           up[1]=ang_3[1];
        }
        else
        {
            up[0]=ang_1[0];
            up[1]=ang_1[1];
        }
        if(up[1]<ang_2[1])
        {
            up[0]=ang_2[0];
            up[1]=ang_2[1];
        }
        left[0]=up[0];
        left[1]=right[1];

        double dopang[2],dopang2[2];
        dopang[0]=up[0];
        dopang[1]=up[1];


        ang_2[0]=D_C[0].pay[(*node)->num];
        ang_2[1]=D_C[6].pay[(*node)->num]-D_C[0].pay[(*node)->num]-D_C[2].pay[(*node)->num];
        ang_2[2]=D_C[2].pay[(*node)->num];

        double left2[2],up2[2];
        temp=ang_2[1]-D_C[4].pay[(*node)->num];
        left2[0]=left[0]+temp;
        left2[1]=left[1];
        up2[1]=left[1]+temp;
        up2[0]=up[0];
        up[1]=D_C[3].pay[(*node)->num];

        double i=0;
        do
        {
           dopang[0]+=i;
           dopang[1]-=i;
           i+=0.1;
        }while(dopang[1]>D_C[3].pay[(*node)->num]);
        dopang[1]=D_C[3].pay[(*node)->num];

        dopang2[0]=dopang[0];
        dopang2[1]=dopang[1];
        while(dopang2[0]<D_C[5].pay[(*node)->num])
        {
           i+=0.1;
           dopang2[0]+=i;
           dopang2[1]-=i;

        }
        dopang2[0]=D_C[5].pay[(*node)->num];
        if(dopang2[1]<left2[1])
        {
            dopang2[1]=left2[1];
        }

        if(D_C[3].pay[(*node)->num]<left2[1]&&D_C[5].pay[(*node)->num]<left2[0])
        {
            left2[0]=D_C[5].pay[(*node)->num];
            left2[1]=D_C[3].pay[(*node)->num];
            up[0]=D_C[5].pay[(*node)->num];
            up[1]=D_C[3].pay[(*node)->num];
            *series0 << QPointF(up[0],up[1]);
            *series1 <<QPointF(left2[0],left2[1]);
        }
        else
        {
            if(left2[0]<D_C[5].pay[(*node)->num])
            {
                double dopang3[2];
                dopang3[0]=D_C[5].pay[(*node)->num];
                dopang3[1]=left2[1];
                *series0 << QPointF(up[0],up[1])<<QPointF(dopang[0],dopang[1])<<QPointF(dopang2[0],dopang2[1])
                        <<QPointF(D_C[5].pay[(*node)->num],up[1]);
                *series1 << QPointF(up2[0],up2[1])<<QPointF(left2[0],left2[1])<<QPointF(dopang3[0],dopang3[1]);
            }
            else
            {
                *series0 << QPointF(up[0],up[1]) <<QPointF(dopang[0],dopang[1])<<QPointF(dopang2[0],dopang2[1])
                        <<QPointF(D_C[5].pay[(*node)->num],up[1]);
                *series1 << QPointF(up2[0],up2[1])<<QPointF(left2[0],left2[1]);
            }
        }



        QAreaSeries *series = new QAreaSeries(series0, series1);
        QString q;
        q.setNum((*node)->num);
        series->setName(q);
        QPen pen(0xb80000);
        pen.setWidth(2);
        series->setPen(pen);

        QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
        gradient.setColorAt(0.0, 0xff2006);
        gradient.setColorAt(1.0, 0xfb1a00);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        series->setBrush(gradient);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Delta C-core");
        chart->createDefaultAxes();

        QValueAxis *axisX = new QValueAxis;
        axisX->setRange(left[0], D_C[5].pay[(*node)->num]);
        axisX->setTickCount(10);
        axisX->setLabelFormat("%.2f");
        QValueAxis *axisY = new QValueAxis;
        axisY->setRange(left[1], up[1]);
        axisY->setTickCount(10);
        axisY->setLabelFormat("%.2f");

        QChartView *chartView = new QChartView(chart);
        chartView->chart()->setAxisX(axisX, series);
        chartView->chart()->setAxisY(axisY, series);
        chartView->setRenderHint(QPainter::Antialiasing);

        DC_window[(*node)->num].setCentralWidget(chartView);
        QDesktopWidget desktop;

        QRect rect = desktop.availableGeometry(desktop.primaryScreen());
        QPoint center = rect.center();
        int x1 = center.x() - (DC_window[(*node)->num].width()/2);
        int y1 = center.y() - (DC_window[(*node)->num].height()/2);
        center.setX(x1);
        center.setY(y1);
        DC_window[(*node)->num].resize(700, 600);
        //DC_window[(*node)->num].show();

        for(int i=0;i<(*node)->child_num;i++)
        {
            DC_Show3(&(*node)->children[i]);
        }

    }
}

solving::~solving()
{

}


