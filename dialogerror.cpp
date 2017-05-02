#include "dialogerror.h"
#include "ui_dialogerror.h"

DialogError::DialogError(QWidget *parent) : QDialog(parent), ui(new Ui::DialogError) {
    ui->setupUi(this);
    setDefaulValues();
    errArea_ = false;
    errSquare_ = false;

    QDialog::connect(ui->buttonBoxAcceptErrors->button(QDialogButtonBox::Ok),SIGNAL(clicked(bool)),this,SLOT(okClicked()));
    QDialog::connect(ui->buttonBoxAcceptErrors->button(QDialogButtonBox::Cancel),SIGNAL(clicked(bool)),this,SLOT(close()));
}

bool DialogError::getStateErrArea() {
    return errArea_;
}

bool DialogError::getStateErrSquare() {
    return errSquare_;
}

void DialogError::okClicked() {
    QMap<QString,cv::Vec3b> colors;
    cv::Vec3b square, area;
    square[0] = (ui->lineEditColorSquare_1->text()).toInt();
    square[1] = (ui->lineEditColorSquare_2->text()).toInt();
    square[2] = (ui->lineEditColorSquare_3->text()).toInt();

    area[0] = (ui->lineEditColorArea_1->text()).toInt();
    area[1] = (ui->lineEditColorArea_2->text()).toInt();
    area[2] = (ui->lineEditColorArea_3->text()).toInt();

    colors["square"] = square;
    colors["area"] = area;

    emit emitErrorColors(colors);

    close();
}

DialogError::~DialogError() {
    delete ui;
}

void DialogError::setDefaulValues() {
    ui->lineEditColorSquare_1->setText("80");
    ui->lineEditColorSquare_2->setText("80");
    ui->lineEditColorSquare_3->setText("80");

    ui->lineEditColorArea_1->setText("80");
    ui->lineEditColorArea_2->setText("80");
    ui->lineEditColorArea_3->setText("80");
}
