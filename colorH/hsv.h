#ifndef HSV_H
#define HSV_H

#include "color.h"

class Hsv : public Color {
public:
    Hsv();
    ~Hsv();
    virtual cv::Vec3b doMeanColor(const std::pair<int,int>& p, int sizeSquare);
    cv::Vec3b& getHsvPixel();
    cv::Vec3b& getHsvSquare();
    cv::Vec3b& getHsvFirstArea();
    cv::Vec3b& getHsvErrSquare();
    cv::Vec3b& getHsvErrArea();

private:
    cv::Vec3b hsvPixel_;
    cv::Vec3b hsvSquare_;
    cv::Vec3b hsvFirstArea_;
    cv::Vec3b hsvErrSquare_;
    cv::Vec3b hsvErrArea_;
};

#endif // HSV_H
