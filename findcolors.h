#ifndef FINDCOLORS_H
#define FINDCOLORS_H

#include <QMainWindow>
#include <QPixmap>
#include <QSize>
#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "video.h"
#include "matrices.h"
#include "colorH/color.h"
#include "colorH/rgb.h"
#include "colorH/hsv.h"

namespace Ui {
class FindColors;
}

class FindColors : public QMainWindow {
    Q_OBJECT

public:
    explicit FindColors(QWidget *parent = 0);
    ~FindColors();
    void defaultStyles();
    void setSizeImg(const QSize& size);
    QSize& getSizeImg();

public slots:
    void processVideo();

private slots:
    void on_radioButtonCamera_clicked();
    void on_radioButtonRGB_clicked();
    void on_radioButtonHSV_clicked();
    void on_radioButtonPhoto_clicked();
    void on_radioButtonInRun_clicked();

private:
    Ui::FindColors *ui;
    QPixmap myPicture_;
    Video video_;
    Matrices matrix_;
    std::vector<std::vector<int>> cMask_;
    QSize size_;
    int sizeSquare_;
    Color *color_;
};

#endif // FINDCOLORS_H













