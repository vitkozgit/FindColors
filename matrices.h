#ifndef MATRICES_H
#define MATRICES_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Matrices {
public:
    Matrices();
    ~Matrices();
    cv::Mat& getWorkMat();
    cv::Mat& getMaskMat();
    cv::Mat& getPictureMat();
    cv::Mat& getTmpMat();
    const cv::String& getNameWorkMat() const;
    const cv::String& getNameMaskMat() const;
    const cv::String& getNamePictureMat() const;

    void setMaskMat(const cv::Mat& mat);
    void setWorkMat(const cv::Mat& workMat);
    void setPictureMat(const cv::Mat& mat);

private:
    cv::Mat workMat_;
    cv::Mat maskMat_;
    cv::Mat pictureMat_;
    cv::String nameWorkMat_;
    cv::String nameMaskMat_;
    cv::String namePictureMat_;
    cv::Mat tmpMat_;
};

#endif // MATRICES_H
