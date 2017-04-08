#include "colorH/rgb.h"

Rgb::Rgb() : rgbPixel_(cv::Vec3b(0,0,0)),
             rgbSquare_(cv::Vec3b(0,0,0)),
             rgbFirstArea_(cv::Vec3b(0,0,0)),
             rgbErrSquare_(cv::Vec3b(0,0,0)),
             rgbErrArea_(cv::Vec3b(0,0,0))
{

}

Rgb::~Rgb() {}

cv::Vec3b Rgb::doMeanColor(const std::pair<int, int> &p, int sizeSquare) {

}

cv::Vec3b& Rgb::getRgbPixel() {
    return rgbPixel_;
}

cv::Vec3b& Rgb::getRgbSquare() {
    return rgbSquare_;
}

cv::Vec3b& Rgb::getRgbFirstArea() {
    return rgbFirstArea_;
}

cv::Vec3b& Rgb::getRgbErrSquare() {
    return rgbErrSquare_;
}

cv::Vec3b& Rgb::getRgbErrArea() {
    return rgbErrArea_;
}
