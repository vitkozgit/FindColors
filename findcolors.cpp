#include "findcolors.h"
#include "ui_findcolors.h"

FindColors::FindColors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindColors)
{
    ui->setupUi(this);
    defaultStyles();
}

FindColors::~FindColors() {
    delete ui;
    delete color_;
}

void FindColors::processVideo() {
    video_.getVideoCapture()->read(matrix_.getWorkMat());
    cv::imshow("Mat",matrix_.getWorkMat());
}

void FindColors::setSizeImg(const QSize& size) {
    size_ = size;
}

QSize& FindColors::getSizeImg() {
    return size_;
}






























