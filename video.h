#ifndef VIDEO_H
#define VIDEO_H

#include <QSize>
#include <memory>
#include <QTimer>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Video {
public:
    Video();
    ~Video();
    std::shared_ptr<QTimer> getTimer() const;
    std::shared_ptr<cv::VideoCapture> getVideoCapture() const;

private:
    std::shared_ptr<QTimer> timer_;
    std::shared_ptr<cv::VideoCapture> videoCapture_;
};


#endif // VIDEO_H
