#include "colorH/rgb.h"

Rgb::Rgb() : rgbPixel_(cv::Vec3b(0,0,0)),
             rgbSquare_(cv::Vec3b(0,0,0)),
             rgbFirstArea_(cv::Vec3b(0,0,0)),
             rgbErrSquare_(cv::Vec3b(0,0,0)),
             rgbErrArea_(cv::Vec3b(0,0,0))
{
    r_ = 0; g_ = 0; b_ = 0;
}

Rgb::~Rgb() {}

void Rgb::doMeanColorFirstSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) {
    double red = 0.0, green = 0.0, blue = 0.0;
    for(int row = p.first - sizeSquare.plusHalfSize_; row <= p.first + sizeSquare.plusHalfSize_; ++row) {
        for(int col = p.second - sizeSquare.plusHalfSize_; col <= p.second + sizeSquare.plusHalfSize_; ++col) {
            cv::Vec3b bgr = mat.at<cv::Vec3b>(row,col);
            blue += bgr[0];
            green += bgr[1];
            red += bgr[2];
        }
    }
    red /= (sizeSquare.size_ * sizeSquare.size_);
    green /= (sizeSquare.size_ * sizeSquare.size_);
    blue /= (sizeSquare.size_ * sizeSquare.size_);

    rgbSquare_ = cv::Vec3b(static_cast<unsigned char>(red),static_cast<unsigned char>(green),static_cast<unsigned char>(blue));
}

cv::Vec3b Rgb::doMeanColorTmpSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) {
    double red = 0.0, green = 0.0, blue = 0.0;
    for(int row = p.first - sizeSquare.plusHalfSize_; row <= p.first + sizeSquare.plusHalfSize_; ++row) {
        for(int col = p.second - sizeSquare.plusHalfSize_; col <= p.second + sizeSquare.plusHalfSize_; ++col) {
            cv::Vec3b bgr = mat.at<cv::Vec3b>(row,col);
            blue += bgr[0];
            green += bgr[1];
            red += bgr[2];
        }
    }
    red /= (sizeSquare.size_ * sizeSquare.size_);
    green /= (sizeSquare.size_ * sizeSquare.size_);
    blue /= (sizeSquare.size_ * sizeSquare.size_);

    cv::Vec3b rgb = cv::Vec3b(static_cast<unsigned char>(red),static_cast<unsigned char>(green),static_cast<unsigned char>(blue));
    return rgb;
}

void Rgb::doColorFirstPixel(const std::pair<int,int>& p, const cv::Mat& mat) {
    unsigned char red, green, blue;
    cv::Vec3b bgr = mat.at<cv::Vec3b>(p.first,p.second);
    blue = bgr[0]; green = bgr[1]; red = bgr[2];
    rgbPixel_ = cv::Vec3b(red,green,blue);
}

bool Rgb::compareColorOfNextSquare(const cv::Vec3b& color) {
    unsigned char red, green, blue;
    unsigned char redErr, greenErr, blueErr;
    red = rgbSquare_[0];
    green = rgbSquare_[1];
    blue = rgbSquare_[2];

    redErr = rgbErrSquare_[0];
    greenErr = rgbErrSquare_[1];
    blueErr = rgbErrSquare_[2];

    if(color[0] > (red + redErr/2) || color[0] < (red - redErr/2)) {
        return false;
    }
    if(color[1] > (green + greenErr/2) || color[1] < (green - greenErr/2)) {
        return false;
    }
    if(color[2] > (blue + blueErr/2) || color[2] < (blue - blueErr/2)) {
        return false;
    }
    return true;
}

bool Rgb::compareColorOfNextArea(const cv::Vec3b& color) {
    unsigned char red, green, blue;
    unsigned char redErr, greenErr, blueErr;
    red = rgbFirstArea_[0];
    green = rgbFirstArea_[1];
    blue = rgbFirstArea_[2];

    redErr = rgbErrArea_[0];
    greenErr = rgbErrArea_[1];
    blueErr = rgbErrArea_[2];

    if(color[0] > (red + redErr/2) || color[0] < (red - redErr/2)) {
        return false;
    }
    if(color[1] > (green + greenErr/2) || color[1] < (green - greenErr/2)) {
        return false;
    }
    if(color[2] > (blue + blueErr/2) || color[2] < (blue - blueErr/2)) {
        return false;
    }
    return true;
}

cv::Vec3b& Rgb::getColorPixel() {
    return rgbPixel_;
}

cv::Vec3b& Rgb::getColorSquare() {
    return rgbSquare_;
}

cv::Vec3b& Rgb::getColorFirstArea() {
    return rgbFirstArea_;
}

cv::Vec3b& Rgb::getColorErrSquare() {
    return rgbErrSquare_;
}

cv::Vec3b& Rgb::getColorErrArea() {
    return rgbErrArea_;
}

void Rgb::setColorPixel(const cv::Vec3b& colorPixel) {
    rgbPixel_ = colorPixel;
}

void Rgb::setColorSquare(const cv::Vec3b& colorSquare) {
    rgbSquare_ = colorSquare;
}

void Rgb::setColorFirstArea(const cv::Vec3b& colorFirstArea) {
    rgbFirstArea_ = colorFirstArea;
}

void Rgb::setColorErrSquare(const cv::Vec3b& colorErrSquare) {
    rgbErrSquare_ = colorErrSquare;
}

void Rgb::setColorErrArea(const cv::Vec3b& colorErrArea) {
    rgbErrArea_ = colorErrArea;
}

void Rgb::addColor(const cv::Vec3b& color) {
    r_ += static_cast<double>(color[0]);
    g_ += static_cast<double>(color[1]);
    b_ += static_cast<double>(color[2]);
}


void Rgb::doMeanColorFirstArea(int size) {
    double red = r_ / static_cast<double>(size);
    double green = g_ / static_cast<double>(size);
    double blue = b_ / static_cast<double>(size);
    cv::Vec3b rgbFirstArea = {static_cast<unsigned char>(red),static_cast<unsigned char>(green),static_cast<unsigned char>(blue)};
    setColorFirstArea(rgbFirstArea);
    r_ = 0.0;
    g_ = 0.0;
    b_ = 0.0;
}










