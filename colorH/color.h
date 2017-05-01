#ifndef COLOR_H
#define COLOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

#include "sizesquare.h"

class Color {
public:
    Color();
    virtual ~Color();
    virtual void doMeanColorFirstSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) = 0;
    virtual void doMeanColorFirstArea(int size) = 0;
    virtual void doColorFirstPixel(const std::pair<int,int>& p, const cv::Mat& mat) = 0;
    virtual cv::Vec3b doMeanColorTmpSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat) = 0;
    virtual bool compareColorOfNextSquare(const cv::Vec3b& color) = 0;
    virtual bool compareColorOfNextArea(const cv::Vec3b& color) = 0;
    virtual void addColor(const cv::Vec3b& color) = 0;
    virtual cv::Vec3b& getColorPixel() = 0;
    virtual cv::Vec3b& getColorSquare() = 0;
    virtual cv::Vec3b& getColorFirstArea() = 0;
    virtual cv::Vec3b& getColorErrSquare() = 0;
    virtual cv::Vec3b& getColorErrArea() = 0;
    virtual void setColorPixel(const cv::Vec3b& colorPixel) = 0;
    virtual void setColorSquare(const cv::Vec3b& colorSquare) = 0;
    virtual void setColorFirstArea(const cv::Vec3b& colorFirstArea) = 0;
    virtual void setColorErrSquare(const cv::Vec3b& colorErrSquare) = 0;
    virtual void setColorErrArea(const cv::Vec3b& colorErrArea) = 0;

};

#endif // COLOR_H
