#ifndef DIALOGERROR_H
#define DIALOGERROR_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVector>
#include <QMap>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class DialogError;
}

class DialogError : public QDialog {
    Q_OBJECT

public:
    explicit DialogError(QWidget *parent = 0);
    ~DialogError();
    void setDefaulValues();
    bool getStateErrArea();
    bool getStateErrSquare();

private slots:
    void okClicked();

signals:
    void emitErrorColors(const QMap<QString,cv::Vec3b>& errorColors);

private:
    Ui::DialogError *ui;
    bool errSquare_;
    bool errArea_;
};

#endif // DIALOGERROR_H
