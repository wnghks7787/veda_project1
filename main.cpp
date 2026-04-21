//main.cpp
#include "login.h"
#include "adminwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Login w;
    //w.show();
    Adminwindow test;
    test.show();
    //Statuswindow status;
    //status.show();
    return QCoreApplication::exec();
}
