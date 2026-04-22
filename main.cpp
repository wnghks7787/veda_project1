//main.cpp
#include "login.h"
#include "adminwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    // return QCoreApplication::exec();
    return a.exec();
}
