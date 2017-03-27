#include "mainwindow.h"
#include <QApplication>
#include "panel_tcp.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //pan.conectTCP(true, 31);
///pan.conectTCP(false, 32);
    //pan.conectTCP(true, 2);
   // pan.conectTCP(true, 2);
    MainWindow w;
    w.show();

    return a.exec();
}
