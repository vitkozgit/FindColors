#include "findcolors.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindColors w;
    QIcon favicon(QDir::currentPath() + "/OtherData/camera.png");
    w.setWindowIcon(favicon);
    w.show();

    return a.exec();
}
