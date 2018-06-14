#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QString>
#include "dialog.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_TwoPL_clicked();

    void on_ThreePL_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *plot;
};

#endif // MAINWINDOW_H
