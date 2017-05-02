#ifndef RGB_H
#define RGB_H

#include "color.h"

class Rgb : public Color {
public:
    Rgb();
    ~Rgb();
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
    virtual const cv::Vec3b &markColor() const;

private:
    cv::Vec3b rgbPixel_;
    cv::Vec3b rgbSquare_;
    cv::Vec3b rgbFirstArea_;
    cv::Vec3b rgbErrSquare_;
    cv::Vec3b rgbErrArea_;
    double r_;
    double g_;
    double b_;
    cv::Vec3b markColorForRgb_;
};

#endif //RGB_H
