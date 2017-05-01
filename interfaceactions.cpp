#include "findcolors.h"
#include "ui_findcolors.h"

void FindColors::on_radioButtonCamera_clicked() {
    video_.getTimer()->start(15);

    //video_.getVideoCapture()->read(matrix_.getWorkMat());
    //size_ = QSize(matrix_.getWorkMat().cols,matrix_.getWorkMat().rows);
    cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));

    ui->radioButtonCamera->setEnabled(false);
    ui->radioButtonVideo->setEnabled(true);
}

void FindColors::on_radioButtonVideo_clicked() {
    video_.getTimer()->stop();
    ui->radioButtonCamera->setEnabled(true);
    ui->radioButtonVideo->setEnabled(false);
}

void FindColors::on_radioButtonRGB_clicked() {
    delete color_;
    color_ = new Rgb();
    ui->radioButtonRGB->setEnabled(false);
    ui->radioButtonHSV->setEnabled(true);

    setAllValueInInterface();
}

void FindColors::on_radioButtonHSV_clicked() {
    delete color_;
    color_ = new Hsv();
    ui->radioButtonRGB->setEnabled(true);
    ui->radioButtonHSV->setEnabled(false);

    setAllValueInInterface();

}

void FindColors::on_radioButtonPhoto_clicked() {
    FindColors::controlClick_ = false;
    points_.getXyGroupPairs().clear();
    cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));

    ui->radioButtonPhoto->setEnabled(false);
    ui->radioButtonInRun->setEnabled(true);

    std::cout << "123" << std::endl;
}

void FindColors::on_radioButtonInRun_clicked() {
    FindColors::controlClick_ = false;
    points_.getXyGroupPairs().clear();
    cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));

    ui->radioButtonPhoto->setEnabled(true);
    ui->radioButtonInRun->setEnabled(false);
}

void FindColors::on_pushButtonSetErrors_clicked() {
    dialogErrors.show();
}

void FindColors::setErrorColors(const QMap<QString,cv::Vec3b>& errorColors) {
    cv::Vec3b square = errorColors["square"];
    cv::Vec3b area = errorColors["area"];

    ui->lcdNumberErrOneS->display(square[0]);
    ui->lcdNumberErrTwoS->display(square[1]);
    ui->lcdNumberErrThreeS->display(square[2]);

    ui->lcdNumberErrOneA->display(area[0]);
    ui->lcdNumberErrTwoA->display(area[1]);
    ui->lcdNumberErrThreeA->display(area[2]);

    color_->setColorErrSquare(square);
    color_->setColorErrArea(area);
}







