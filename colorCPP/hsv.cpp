#include "colorH/hsv.h"

Hsv::Hsv() : hsvPixel_(cv::Vec3b(0,0,0)),
             hsvSquare_(cv::Vec3b(0,0,0)),
             hsvFirstArea_(cv::Vec3b(0,0,0)),
             hsvErrSquare_(cv::Vec3b(0,0,0)),
             hsvErrArea_(cv::Vec3b(0,0,0)),
             markColorForHsv_(cv::Vec3b(60,255,255))
{
    h_ = 0.0; s_ = 0.0; v_ = 0.0;

}

Hsv::~Hsv() {}

void Hsv::doMeanColorFirstSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) {
    double hue = 0.0, saturation = 0.0, value = 0.0;
    for(int row = p.first - sizeSquare.plusHalfSize_; row <= p.first + sizeSquare.plusHalfSize_; ++row) {
        for(int col = p.second - sizeSquare.plusHalfSize_; col <= p.second + sizeSquare.plusHalfSize_; ++col) {
            cv::Vec3b hsv = mat.at<cv::Vec3b>(row,col);
            hue += hsv[0];
            saturation += hsv[1];
            value += hsv[2];
        }
    }
    hue /= (sizeSquare.size_ * sizeSquare.size_);
    saturation /= (sizeSquare.size_ * sizeSquare.size_);
    value /= (sizeSquare.size_ * sizeSquare.size_);

    hsvSquare_ = cv::Vec3b(static_cast<unsigned char>(hue),static_cast<unsigned char>(saturation),static_cast<unsigned char>(value));
}

cv::Vec3b Hsv::doMeanColorTmpSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) {
    double hue = 0.0, saturation = 0.0, value = 0.0;
    for(int row = p.first - sizeSquare.plusHalfSize_; row <= p.first + sizeSquare.plusHalfSize_; ++row) {
        for(int col = p.second - sizeSquare.plusHalfSize_; col <= p.second + sizeSquare.plusHalfSize_; ++col) {
            cv::Vec3b hsv = mat.at<cv::Vec3b>(row,col);
            hue += hsv[0];
            saturation += hsv[1];
            value += hsv[2];
        }
    }
    hue /= (sizeSquare.size_ * sizeSquare.size_);
    saturation /= (sizeSquare.size_ * sizeSquare.size_);
    value /= (sizeSquare.size_ * sizeSquare.size_);

    cv::Vec3b hsv = cv::Vec3b(static_cast<unsigned char>(hue),static_cast<unsigned char>(saturation),
                              static_cast<unsigned char>(value));
    return hsv;
}

void Hsv::doColorFirstPixel(const std::pair<int,int>& p, const cv::Mat& mat) {
    unsigned char hue, saturation, value;
    cv::Vec3b hsv = mat.at<cv::Vec3b>(p.first,p.second);
    hue = hsv[0]; saturation = hsv[1]; value = hsv[2];
    hsvPixel_ = cv::Vec3b(hue,saturation,value);
}

bool Hsv::compareColorOfNextSquare(const cv::Vec3b& color) {
    unsigned char hue, saturation, value;
    unsigned char hueErr, saturationErr, valueErr;
    hue = hsvSquare_[0];
    saturation = hsvSquare_[1];
    value = hsvSquare_[2];

    hueErr = hsvErrSquare_[0];
    saturationErr = hsvErrSquare_[1];
    valueErr = hsvErrSquare_[2];

    if(color[0] > (hue + hueErr/2) || color[0] < (hue - hueErr/2)) {
        return false;
    }
    if(color[1] > (saturation + saturationErr/2) || color[1] < (saturation - saturationErr/2)) {
        return false;
    }
    if(color[2] > (value + valueErr/2) || color[2] < (value - valueErr/2)) {
        return false;
    }
    return true;
}

bool Hsv::compareColorOfNextArea(const cv::Vec3b& color) {
    unsigned char hue, saturation, value;
    unsigned char hueErr, saturationErr, valueErr;
    hue = hsvFirstArea_[0];
    saturation = hsvFirstArea_[1];
    value = hsvFirstArea_[2];

    hueErr = hsvErrArea_[0];
    saturationErr = hsvErrArea_[1];
    valueErr = hsvErrArea_[2];

    if(color[0] > (hue + hueErr/2) || color[0] < (hue - hueErr/2)) {
        return false;
    }
    if(color[1] > (saturation + saturationErr/2) || color[1] < (saturation - saturationErr/2)) {
        return false;
    }
    if(color[2] > (value + valueErr/2) || color[2] < (value - valueErr/2)) {
        return false;
    }
    return true;
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
    h_ += static_cast<double>(color[0]);
    s_ += static_cast<double>(color[1]);
    v_ += static_cast<double>(color[2]);
}

void Hsv::doMeanColorFirstArea(int size) {
    double hue = h_ / static_cast<double>(size);
    double saturation = s_ / static_cast<double>(size);
    double value = v_ / static_cast<double>(size);
    cv::Vec3b hsvFirstArea = {static_cast<unsigned char>(hue),static_cast<unsigned char>(saturation),
                              static_cast<unsigned char>(value)};
    setColorFirstArea(hsvFirstArea);
    h_ = 0.0;
    s_ = 0.0;
    v_ = 0.0;
}

const cv::Vec3b& Hsv::markColor() const {
    return markColorForHsv_;
}




