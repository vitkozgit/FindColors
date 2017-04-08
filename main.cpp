#include "findcolors.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FindColors w;

////////////////////////////////////////////////////////////////
    cv::Vec3b vec(0,2,123);
    //std::cout << static_cast<int>(vec[0]) << std::endl;
    std::cout << (int)vec[2] << std::endl;
    int x = vec[0];
    std::cout << x << std::endl;

    uchar xx = 3, yy = 5, zz;
    zz = xx * xx + yy * yy;
    std::cout << (int)zz << std::endl;
/////////////////////////////////////////////////////////////////

    return a.exec();
}
