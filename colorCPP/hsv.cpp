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

void Hsv::doMeanColorFirstSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) {

}

cv::Vec3b Hsv::doMeanColorTmpSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) {

}

void Hsv::doColorFirstPixel(const std::pair<int,int>& p, const cv::Mat& mat) {

}

bool Hsv::compareColorOfNextSquare(const cv::Vec3b& color) {

}

cv::Vec3b& Hsv::getColorPixel() {
    return hsvPixel_;
}

cv::Vec3b& Hsv::getColorSquare() {
    return hsvSquare_;
}

cv::Vec3b& Hsv::getColorFirstArea() {
    return hsvFirstArea_;
}

cv::Vec3b& Hsv::getColorErrSquare() {
    return hsvErrSquare_;
}

cv::Vec3b& Hsv::getColorErrArea() {
    return hsvErrArea_;
}

void Hsv::setColorPixel(const cv::Vec3b& colorPixel) {
    hsvPixel_ = colorPixel;
}

void Hsv::setColorSquare(const cv::Vec3b& colorSquare) {
    hsvSquare_ = colorSquare;
}

void Hsv::setColorFirstArea(const cv::Vec3b& colorFirstArea) {
    hsvFirstArea_ = colorFirstArea;
}

void Hsv::setColorErrSquare(const cv::Vec3b& colorErrSquare) {
    hsvErrSquare_ = colorErrSquare;
}

void Hsv::setColorErrArea(const cv::Vec3b& colorErrArea) {
    hsvErrArea_ = colorErrArea;
}

void Hsv::addColor(const cv::Vec3b& color) {

}

void Hsv::doMeanColorFirstArea(int size) {

}

bool Hsv::compareColorOfNextArea(const cv::Vec3b& color) {

}






