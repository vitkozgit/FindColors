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
#include "dialogerror.h"

namespace Ui {
class FindColors;
}

class FindColors : public QMainWindow {
    Q_OBJECT

public:
    explicit FindColors(QWidget *parent = 0);
    ~FindColors();
    void defaultStyles();
    void setAllValueInInterface();
    void setSizeImg(const QSize& size);
    QSize& getSizeImg();
    XyPoints& getXyPoints();

    static bool controlClick_;

    void findFirstArea(const std::pair<int,int>& yx);
    void findArea(const std::pair<int, int>& yx);
    void findAllPoints();

    template <typename T>
    void drawOneSquare(const std::pair<int,int>& yx, cv::Mat &mat, T color);
    template <typename T>
    void draw(const std::vector<std::vector<std::pair<int,int>>>& groupsYX, cv::Mat &mat, T color);
    void drawMask(const std::vector<std::vector<std::pair<int,int>>>& groupsYX, cv::Mat& mat);
    bool controlClick(int x, int y);
    bool isPointBelongsToField(const std::pair<int,int>& yx);
    void setTrueElementsOfMask(const std::pair<int, int>& yx);
    bool hasTrueElementsInSquare(const std::pair<int, int>& yx);
    void wholeChecking(const std::pair<int, int>& yx, std::queue<std::pair<int, int>>& queue);
    void wholeCheckingFirst(const std::pair<int, int>& tmpYX, std::queue<std::pair<int,int>>& queue);
    void setErrorColors();


public slots:
    void processVideo();
    void setErrorColors(const QMap<QString,cv::Vec3b>& errorColors);

private slots:
    void on_radioButtonCamera_clicked();
    void on_radioButtonRGB_clicked();
    void on_radioButtonHSV_clicked();
    void on_radioButtonPhoto_clicked();
    void on_radioButtonInRun_clicked();

    void on_pushButtonSetErrors_clicked();

    void on_radioButtonVideo_clicked();

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
    DialogError dialogErrors;
};

#endif // FINDCOLORS_H













