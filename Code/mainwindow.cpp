#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_TwoPL_clicked()
{
    ui->TwoPL->hide();
    ui->ThreePL->hide();
    ui->label->setText("Close when work is finished");
    ui->label_2->setVisible(false);
     ui->Question->setVisible(false);
    plot = new Dialog(this);
    plot->players=2;
    plot->show();
}

void MainWindow::on_ThreePL_clicked()
{

    ui->ThreePL->hide();
    ui->TwoPL->hide();

    ui->label->setText("Close when work is finished");
    ui->label_2->setVisible(false);
    ui->Question->setVisible(false);
    plot = new Dialog(this);
    plot->players=3;
    plot->show();

}


