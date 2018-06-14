#ifndef COOP_H
#define COOP_H

class coop
{

public:
    int *pl;
    double *pay;
    void Show();
    void mShow();
    int pl_num;
    int node;
    coop(int, int);
    int GetNode(int);

    ~coop();
};

#endif // COOP_H
