#ifndef MATRICES_H
#define MATRICES_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Matrices {
public:
    cv::Mat& getWorkMat();
    cv::Mat& getMaskMat();
    cv::Mat& getPictureMat();
private:
    cv::Mat workMat_;
    cv::Mat maskMat_;
    cv::Mat pictureMat_;
};

#endif // MATRICES_H
