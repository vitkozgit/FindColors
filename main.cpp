#include "findcolors.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindColors w;
    w.show();

    return a.exec();
}
