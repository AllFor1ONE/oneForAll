#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login loginA;
    loginA.show();
    return a.exec();
}
