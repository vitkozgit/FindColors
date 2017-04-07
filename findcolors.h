#ifndef FINDCOLORS_H
#define FINDCOLORS_H

#include <QMainWindow>

namespace Ui {
class FindColors;
}

class FindColors : public QMainWindow
{
    Q_OBJECT

public:
    explicit FindColors(QWidget *parent = 0);
    ~FindColors();

private:
    Ui::FindColors *ui;
};

#endif // FINDCOLORS_H
