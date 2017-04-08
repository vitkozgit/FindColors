#include "findcolors.h"
#include "ui_findcolors.h"

void FindColors::defaultStyles() {
    QSize size = ui->labelPicture->size();
    myPicture_ = QPixmap("/home/vitali/Projects/Zadanie_5_NEW/FindColors/Resources/War.jpg");
    ui->labelPicture->setPixmap(myPicture_.scaled(size,Qt::KeepAspectRatio));

    ui->lcdNumberErrOne->display(40);
    ui->lcdNumberErrTwo->display(40);
    ui->lcdNumberErrThree->display(40);

    ui->lcdNumberOne->display(0);
    ui->lcdNumberTwo->display(0);
    ui->lcdNumberThree->display(0);

    ui->radioButtonRGB->setChecked(true);
    ui->radioButtonPhoto->setChecked(true);
}
