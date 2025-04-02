#include <QApplication>
#include "include/screens/loginscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginScreen screen;
    screen.show();

    return a.exec();
}
