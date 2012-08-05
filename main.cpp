#include <QApplication>
#include <QtGui>
#include "mainwindow.h"

#include "imagesmodel.h"

int fsPrescan()
{
    return -1;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
