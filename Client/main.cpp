#include <QtGui/QApplication>
#include "windowcontrol.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowControl::changeWindow();


    //return a.exec();
    return 0;

}
