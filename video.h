#ifndef VIDEO_H
#define VIDEO_H

#include <QSize>
#include <QTimer>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <memory>

class Video {
public:
    Video();
    ~Video();
    std::shared_ptr<QTimer> getTimer() const;
    std::shared_ptr<cv::VideoCapture> getVideoCapture() const;
    const QString& getPath() const;
    void setPath(const QString& path);

private:
    std::shared_ptr<QTimer> timer_;
    std::shared_ptr<cv::VideoCapture> videoCapture_;
    QString path_;
};


#endif // VIDEO_H
