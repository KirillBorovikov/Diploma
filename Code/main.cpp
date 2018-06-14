#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <iostream>


int main(int argc, char *argv[])
{
   QStringList paths = QCoreApplication::libraryPaths();
   paths.append(".");
   paths.append("imageformats");
   paths.append("platforms");
   paths.append("sqldrivers");
   QCoreApplication::setLibraryPaths(paths);

   QApplication a(argc, argv);
   MainWindow q;
   q.show();

   return a.exec();
}
