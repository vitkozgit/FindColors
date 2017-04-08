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

namespace Ui {
class FindColors;
}

class FindColors : public QMainWindow {
    Q_OBJECT

public:
    explicit FindColors(QWidget *parent = 0);
    ~FindColors();
    void defaultStyles();
    void setSizeImg(const QSize& sizeImg);
    auto getSizeImg() const;

public slots:
    void processVideo();

private slots:
    void on_radioButtonCamera_clicked();

private:
    Ui::FindColors *ui;
    QPixmap myPicture_;
    Video video_;
    cv::Mat mat_;
    QSize size_;
    std::vector<std::vector<std::pair<int,int>>> cMask;
};

#endif // FINDCOLORS_H













