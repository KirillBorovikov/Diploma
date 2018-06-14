#ifndef DIALOG_H
#define DIALOG_H
#include <iostream>
#include <QMessageBox>
#include <fstream>
#include "game2.h"
#include "game3.h"
#include "Element.h"
#include "winery2.h"
#include "winery3.h"
#include "tree2.h"
#include "tree3.h"
#include "solving.h"
#include "coop.h"
#include "dialog.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    solving *G1;
    int players=0;
    int nodes=0;
    int check;
    Game2 *z;
    Game3 *z3;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_File_clicked();


    void on_Save_clicked();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H


