#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::Dialog)
{
   ui->setupUi(this);

   ui->pushButton->setVisible(false);
   ui->pushButton_2->setVisible(false);
   ui->Number->setVisible(false);
   ui->Number_2->setVisible(false);
   ui->spinBox->setVisible(false);
   ui->spinBox_2->setVisible(false);
   ui->Save->setVisible(false);
   ui->Result->setVisible(false);
   ui->Title->setText("Select data input type");
   check=0;

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    int num=ui->spinBox->value();
    G1->C_window[num].show();
}

void Dialog::on_pushButton_2_clicked()
{
    int num1=ui->spinBox_2->value();
    G1->DC_window[num1].show();
}

void Dialog::on_File_clicked()
{

    switch (players)
    {
     case 2:
     {
        int i=0,j=0,ch=0,ii=0;

        ifstream in("Resources\\Data2.txt");
        in>>ii;
        nodes=ii;
        z = (Game2*)operator new( sizeof(Game2) *nodes);
        for(int ix=0;ix<nodes;ix++)
            {
                in>>i;
                in>>j;
                in>>ch;
                new(&z[check]) Game2(players,i,j,ch,check);
                check+=1;
            }

            tree2 gm(z[0]);
            float parent,q;
            for(int ix=1;ix<nodes;ix++)
            {
                in>>parent;
                in>>q;
                gm.push(&gm.head,parent,z[ix],q,false);

            }
            in.close();
            gm.Show(gm.head);
            G1=new solving(players,nodes,&gm.head);

            ui->File->setVisible(false);

            ui->pushButton->setVisible(true);
            ui->pushButton_2->setVisible(true);
            ui->Number->setVisible(true);
            ui->Number_2->setVisible(true);
            ui->spinBox->setVisible(true);
            ui->spinBox_2->setVisible(true);
            ui->Title->setText("Input node number to see the plot");
            ui->Save->setVisible(true);
            ui->spinBox->setMaximum(nodes-1);
            ui->spinBox_2->setMaximum(nodes-1);

            //gm.sVer(gm.head);


        break;
     }
     case 3:
     {

        int i=0,j=0,ch=0,ii=0,M=0;

        ifstream in("Resources\\Data3.txt");
        in>>ii;
        nodes=ii;
        z3 = (Game3*)operator new( sizeof(Game3) *nodes);
        for(int ix=0;ix<nodes;ix++)
            {
                in>>i;
                in>>j;
                in>>M;
                in>>ch;
                new(&z3[check]) Game3(players,i,j,M,ch,check);
                check+=1;
            }

            tree3 gm(z3[0],0.5);
            float parent,q,ver;
            for(int ix=1;ix<nodes;ix++)
            {
                in>>parent;
                in>>q;
                in>>ver;
                gm.push(&gm.head,parent,z3[ix],q,ver,false);

            }
            in.close();
            //gm.Show(gm.head);
            gm.sVer(&gm.head);

            G1=new solving(players,nodes,&gm.head);

            ui->File->setVisible(false);

            ui->pushButton->setVisible(true);
            ui->pushButton_2->setVisible(true);
            ui->Number->setVisible(true);
            ui->Number_2->setVisible(true);
            ui->spinBox->setVisible(true);
            ui->spinBox_2->setVisible(true);
            ui->Title->setText("Input node number to see the plot");
            ui->Save->setVisible(true);
            ui->spinBox->setMaximum(nodes-1);
            ui->spinBox_2->setMaximum(nodes-1);

        break;
     }

    }

}

void Dialog::on_Save_clicked()
{
    ofstream ofs("Output\\Cores_Output.txt");
    ofs<<"--------------------------------------------------------------"<<endl;
    ofs<<"|                       For C-core:                          |"<<endl;
    ofs<<"--------------------------------------------------------------"<<endl;
    bool check=false;
    for(int i=0;i<G1->nodes;i++)
    {
        ofs<<"|Z"<<i<<":"<<endl;
        for(int j=0;j<G1->number;j++)
        {

             ofs<<"|   ";
             for(int ix=0;ix<players;ix++)
             {

                 if(G1->C[j].pl[ix]!=0)
                 {
                     if(check==true)
                     {
                       ofs<<" + ";
                     }
                     ofs<<"α";
                     ofs<<G1->C[j].pl[ix];
                     check=true;
                 }

             }
             if(j!=G1->number-1)
             {
                 ofs<<" ⩾ "<<G1->C[j].pay[i]<<endl;

                 check=false;
             }
             else
             {
                 ofs<<" = "<<G1->C[j].pay[i]<<endl;
                 check=false;
             }
        }
        ofs<<"------------------------------"<<endl;
    }
    ofs<<endl;
    ofs<<"--------------------------------------------------------------"<<endl;
    ofs<<"|                       For Delta-core:                      |"<<endl;
    ofs<<"--------------------------------------------------------------"<<endl;

    for(int i=0;i<G1->nodes;i++)
    {
        ofs<<"|Z"<<i<<":"<<endl;
        for(int j=0;j<G1->number;j++)
        {

             ofs<<"|   ";
             for(int ix=0;ix<players;ix++)
             {

                 if(G1->D_C[j].pl[ix]!=0)
                 {
                     if(check==true)
                     {
                       ofs<<" + ";
                     }
                     ofs<<"α";
                     ofs<<G1->D_C[j].pl[ix];
                     check=true;
                 }

             }
             if(j!=G1->number-1)
             {
                 ofs<<" ⩾ "<<G1->D_C[j].pay[i]<<endl;

                 check=false;
             }
             else
             {
                 ofs<<" = "<<G1->D_C[j].pay[i]<<endl;
                 check=false;
             }
        }
        ofs<<"------------------------------"<<endl;
    }
    ui->Result->setVisible(true);
    ofs.close();
    ui->Save->setVisible(false);
}
