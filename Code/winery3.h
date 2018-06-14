#ifndef WINERY3_H
#define WINERY3_H
#include <string>
#include "winery2.h"
#include "element.h"
using namespace std;

class Winery3 : public Winery2
{
public:
    Element ***position;
    int M;
    Winery3(int,int,int,int);

    void Show();
    void Fill(char[]);
    ~Winery3();
    void v_Show();
};

#endif // WINERY3_H
