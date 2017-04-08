#include "colorH/hsv.h"

Hsv::Hsv() : hsvPixel_(cv::Vec3b(0,0,0)),
             hsvSquare_(cv::Vec3b(0,0,0)),
             hsvFirstArea_(cv::Vec3b(0,0,0)),
             hsvErrSquare_(cv::Vec3b(0,0,0)),
             hsvErrArea_(cv::Vec3b(0,0,0))
{

}

Hsv::~Hsv() {

}

cv::Vec3b Hsv::doMeanColor(const std::pair<int, int> &p, int sizeSquare) {

}

cv::Vec3b& Hsv::getHsvPixel() {
    return hsvPixel_;
}

cv::Vec3b& Hsv::getHsvSquare() {
    return hsvSquare_;
}

cv::Vec3b& Hsv::getHsvFirstArea() {
    return hsvFirstArea_;
}

cv::Vec3b& Hsv::getHsvErrSquare() {
    return hsvErrSquare_;
}

cv::Vec3b& Hsv::getHsvErrArea() {
    return hsvErrArea_;
}
