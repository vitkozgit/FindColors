#include "video.h"

Video::Video() {
    videoCapture_ = std::make_shared<cv::VideoCapture>(Q_NULLPTR);
    timer_ = std::make_shared<QTimer>(Q_NULLPTR);
}

Video::~Video() {}


std::shared_ptr<QTimer> Video::getTimer() const {
    return timer_;
}

std::shared_ptr<cv::VideoCapture> Video::getVideoCapture() const {
    return videoCapture_;
}
