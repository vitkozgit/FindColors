#ifndef FINDCOLORS_H
#define FINDCOLORS_H

// lib Qt
#include <QMainWindow>
#include <QPixmap>
#include <QSize>
#include <QDir>

// lib std, boost
#include <memory>
#include <vector>
#include <functional>
#include <queue>

// lib openCV
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// my lib
#include "video.h"
#include "matrices.h"
#include "colorH/color.h"
#include "colorH/rgb.h"
#include "colorH/hsv.h"
#include "xypoints.h"
#include "sizesquare.h"

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

    XyPoints& getXyPoints();

    static bool controlClick_;

    void findFirstArea(const std::pair<int,int>& yx);
    void drawOneSquare(const std::pair<int,int>& yx, cv::Mat &mat);
    void draw(const std::vector<std::vector<std::pair<int,int>>>& groupsYX, cv::Mat &mat);
    bool controlClick(int x, int y);
    bool isPointBelongsToField(const std::pair<int,int>& yx);
    void setTrueElementsOfMask(const std::pair<int, int>& yx);
    bool hasTrueElementsInSquare(const std::pair<int, int>& yx);
    void wholeChecking(const std::pair<int, int>& yx, std::queue<std::pair<int, int>>& queue);



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
    Color *color_;
    QSize size_;
    XyPoints points_;
    SizeSquare sizeSquare_;

    //Will be changed
//    int sizeSquare_;
//    int minusSizeSquare_;
//    int plusSizeSquare_;
};

#endif // FINDCOLORS_H













