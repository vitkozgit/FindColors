#ifndef COLOR_H
#define COLOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

class Color {
public:
    Color();
    virtual ~Color();
    virtual cv::Vec3b doMeanColor(const std::pair<int,int>& p, int sizeSquare) = 0;
};

#endif // COLOR_H
