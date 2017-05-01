#include "matrices.h"

Matrices::Matrices() : nameWorkMat_("Video"),
                       nameMaskMat_("Maska"),
                       namePictureMat_("Obrazek")
{

}

Matrices::~Matrices() {}

cv::Mat& Matrices::getWorkMat() {
    return workMat_;
}

cv::Mat& Matrices::getMaskMat() {
    return maskMat_;
}

cv::Mat& Matrices::getPictureMat() {
    return pictureMat_;
}

const cv::String& Matrices::getNameWorkMat() const {
    return nameWorkMat_;
}

const cv::String& Matrices::getNameMaskMat() const {
    return nameMaskMat_;
}

const cv::String& Matrices::getNamePictureMat() const {
    return namePictureMat_;
}

void Matrices::setPictureMat(const cv::Mat& mat) {
    pictureMat_ = mat;
}

void Matrices::setMaskMat(const cv::Mat& mat) {
    maskMat_ = mat;
}
