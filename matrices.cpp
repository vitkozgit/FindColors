#include "matrices.h"

cv::Mat &Matrices::getWorkMat() {
    return workMat_;
}

cv::Mat& Matrices::getMaskMat() {
    return maskMat_;
}

cv::Mat& Matrices::getPictureMat() {
    return pictureMat_;
}
