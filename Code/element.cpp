#include "element.h"
#include <iostream>

using namespace std;
Element::Element()
{
    pl=2;
    el = new double[pl];

    for (int ix = 0; ix < pl; ix++)
    {
       el[ix] = 0;
    }
    ver=0;

}


void Element::verShow()
{
    for (int ix = 0; ix < nodes; ix++)
    {
       std::cout<<ver[ix]<<' ';
    }
}
void Element::Show()
{
    for(int ix=0; ix<pl; ix++)
    {
        std::cout<<el[ix]<<' ';
    }
}

int Element::GetEl(int g)
{
    for(int ix=0; ix<pl; ix++)
    {
        if(ix==g)
        {
            return el[ix];
            break;
        }
    }
}

bool Element::checkEl(int i)
{
  if(i<pl)
  {
     return true;
  }
  else
  {
      return false;
  }
}

void Element::SetMagic(int play)
{
    pl=play;
    el = new double[pl];
    for (int ix = 0; ix < pl; ix++)
    {
       el[ix] = 0;
    }

}

void Element::SetVer(int n)
{
    nodes=n;
    ver = new double[nodes];
    for (int ix = 0; ix < nodes; ix++)
    {
       ver[ix] = 0;
    }
}

void Element::setEl(int i, double num)
{
   el[i]=num;
}

Element::~Element()
{
    delete  [] el;
}

