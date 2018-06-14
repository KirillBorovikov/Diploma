#ifndef WINERY2_H
#define WINERY2_H
#include <string>
#include "element.h"
using namespace std;
class Winery2
{
public:
    Element **position;

    int i;
    int j;
    int players;
    Winery2(int,int,int);
    void Show();
    void Fill(char[]);
    ~Winery2();
    void v_Show();
};

#endif // WINERY2_H
