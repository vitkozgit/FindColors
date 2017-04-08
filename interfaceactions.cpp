#include "findcolors.h"
#include "ui_findcolors.h"

void FindColors::on_radioButtonCamera_clicked() {
    video_.getVideoCapture()->open(0);
    QObject::connect(video_.getTimer().get(),SIGNAL(timeout()),this, SLOT(processVideo()));
    video_.getTimer()->start(15);

    video_.getVideoCapture()->read(matrix_.getWorkMat());
    size_ = QSize(matrix_.getWorkMat().cols,matrix_.getWorkMat().rows);
    cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));
}

void FindColors::on_radioButtonRGB_clicked() {
    delete color_;
    color_ = new Rgb();
    ui->radioButtonRGB->setEnabled(false);
    ui->radioButtonHSV->setEnabled(true);
}

void FindColors::on_radioButtonHSV_clicked() {
    delete color_;
    color_ = new Hsv();
    ui->radioButtonRGB->setEnabled(true);
    ui->radioButtonHSV->setEnabled(false);
}

void FindColors::on_radioButtonPhoto_clicked() {

}

void FindColors::on_radioButtonInRun_clicked() {

}
