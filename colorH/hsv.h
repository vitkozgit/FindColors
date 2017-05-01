#ifndef HSV_H
#define HSV_H

#include "color.h"

class Hsv : public Color {
public:
    Hsv();
    ~Hsv();
    virtual void doMeanColorFirstSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat);
    virtual void doMeanColorFirstArea(int size);
    virtual cv::Vec3b doMeanColorTmpSquare(const std::pair<int,int>& p, const SizeSquare& sizeSquare, const cv::Mat& mat);
    virtual void doColorFirstPixel(const std::pair<int,int>& p, const cv::Mat& mat);
    virtual bool compareColorOfNextSquare(const cv::Vec3b& color);
    virtual bool compareColorOfNextArea(const cv::Vec3b& color);
    virtual void addColor(const cv::Vec3b& color);
    virtual cv::Vec3b& getColorPixel();
    virtual cv::Vec3b& getColorSquare();
    virtual cv::Vec3b& getColorFirstArea();
    virtual cv::Vec3b& getColorErrSquare();
    virtual cv::Vec3b& getColorErrArea();
    virtual void setColorPixel(const cv::Vec3b& colorPixel);
    virtual void setColorSquare(const cv::Vec3b& colorSquare);
    virtual void setColorFirstArea(const cv::Vec3b& colorFirstArea);
    virtual void setColorErrSquare(const cv::Vec3b& colorErrSquare);
    virtual void setColorErrArea(const cv::Vec3b& colorErrArea);

private:
    cv::Vec3b hsvPixel_;
    cv::Vec3b hsvSquare_;
    cv::Vec3b hsvFirstArea_;
    cv::Vec3b hsvErrSquare_;
    cv::Vec3b hsvErrArea_;
};

#endif // HSV_H
