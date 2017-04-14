#include "findcolors.h"
#include "ui_findcolors.h"

void FindColors::defaultStyles() {
    QSize size = ui->labelPicture->size();
    //QDir myDir = QDir::currentPath();
    auto path = QApplication::applicationDirPath();
    myPicture_ = QPixmap("/home/vitali/Projects/Zadanie_5_NEW/FindColors/Resources/War.jpg");
    ui->labelPicture->setPixmap(myPicture_.scaled(size,Qt::KeepAspectRatio));

    ui->lcdNumberErrOneS->display(40);
    ui->lcdNumberErrTwoS->display(40);
    ui->lcdNumberErrThreeS->display(40);

    ui->lcdNumberOneS->display(0);
    ui->lcdNumberTwoS->display(0);
    ui->lcdNumberThreeS->display(0);

    ui->lcdNumberErrOneA->display(40);
    ui->lcdNumberErrTwoA->display(40);
    ui->lcdNumberErrThreeA->display(40);

    ui->lcdNumberOneA->display(0);
    ui->lcdNumberTwoA->display(0);
    ui->lcdNumberThreeA->display(0);

    ui->radioButtonRGB->setChecked(true);
    ui->radioButtonPhoto->setChecked(true);

    color_ = new Rgb();
    ui->radioButtonRGB->setEnabled(false);
    ui->radioButtonHSV->setEnabled(true);

    color_->setColorErrSquare(cv::Vec3b(ui->lcdNumberErrOneS->value(),
                                        ui->lcdNumberErrTwoS->value(),
                                        ui->lcdNumberErrThreeS->value()));
    color_->setColorErrArea(cv::Vec3b(ui->lcdNumberErrOneA->value(),
                                      ui->lcdNumberErrTwoA->value(),
                                      ui->lcdNumberErrThreeA->value()));


}




