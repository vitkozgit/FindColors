#include "findcolors.h"
#include "ui_findcolors.h"

FindColors::FindColors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindColors)
{
    ui->setupUi(this);
}

FindColors::~FindColors()
{
    delete ui;
}
