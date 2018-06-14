#ifndef ELEMENT_H
#define ELEMENT_H


class Element
{
public:
    double *ver;
    int nodes;
    double *el;
    int pl;
    Element();
    void Show();
    int GetEl(int);
    bool checkEl(int);
    void SetMagic(int);//Да смилостяться над нами боги...
    void SetVer(int);
    void setEl(int,double);
    void verShow();
    ~Element();
};

#endif // ELEMENT_H
