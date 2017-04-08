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
}

void FindColors::processVideo() {
    video_.getVideoCapture()->read(mat_);
    cv::imshow("Mat",mat_);
}

void FindColors::on_radioButtonCamera_clicked() {
    video_.getVideoCapture()->open(0);
    QObject::connect(video_.getTimer().get(),SIGNAL(timeout()),this, SLOT(processVideo()));
    video_.getTimer()->start(20);

    video_.getVideoCapture()->read(mat_);
    size_ = QSize(mat_.cols,mat_.rows);
}

void FindColors::setSizeImg(const QSize& size) {
    size_ = size;
}

auto FindColors::getSizeImg() const {
    return size_;
}














