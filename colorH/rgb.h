#ifndef RGB_H
#define RGB_H

#include "color.h"

class Rgb : public Color {
public:
    Rgb();
    ~Rgb();
    virtual cv::Vec3b doMeanColor(const std::pair<int,int>& p, int sizeSquare);
    cv::Vec3b& getRgbPixel();
    cv::Vec3b& getRgbSquare();
    cv::Vec3b& getRgbFirstArea();
    cv::Vec3b& getRgbErrSquare();
    cv::Vec3b& getRgbErrArea();
private:
    cv::Vec3b rgbPixel_;
    cv::Vec3b rgbSquare_;
    cv::Vec3b rgbFirstArea_;
    cv::Vec3b rgbErrSquare_;
    cv::Vec3b rgbErrArea_;
};

#endif //RGB_H
