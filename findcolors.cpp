#include "findcolors.h"
#include "ui_findcolors.h"

bool FindColors::controlClick_ = false;

FindColors::FindColors(QWidget *parent) : QMainWindow(parent), ui(new Ui::FindColors), sizeSquare_(7) {
    ui->setupUi(this);
    defaultStyles();

    ui->radioButtonHSV->setVisible(true);
    ui->radioButtonVideo->setVisible(true);
    int height = 480;
    int width = 640;

    size_ = QSize(width, height);

    video_.getVideoCapture()->open(0);

    QObject::connect(video_.getTimer().get(),SIGNAL(timeout()),this, SLOT(processVideo()));
    QObject::connect(myVideo_.getTimer().get(),SIGNAL(timeout()),this, SLOT(processVideo()));
    QObject::connect(&dialogErrors_,SIGNAL(emitErrorColors(QMap<QString,cv::Vec3b>)),SLOT(setErrorColors(QMap<QString,cv::Vec3b>)));
}

FindColors::~FindColors() {
    delete ui;
    delete color_;
}

void FindColors::processVideo() {
    //łapie obraz i wczytuje (dwa działania na raz zamias grab i retrieve)
    if(ui->radioButtonCamera->isChecked()) {
        video_.getVideoCapture()->read(matrix_.getWorkMat());
    } else if(ui->radioButtonVideo->isChecked()) {
            myVideo_.getVideoCapture()->read(matrix_.getWorkMat());
            if(matrix_.getWorkMat().empty()) {
                myVideo_.getTimer()->stop();
                std::cout << "1234" << std::endl;
                matrix_.setWorkMat(matrix_.getTmpMat());
            }
    }
    cv::resize(matrix_.getWorkMat(),matrix_.getWorkMat(),cv::Size(size_.rwidth(),size_.rheight()));
    if(ui->radioButtonHSV->isChecked()) {
        cv::cvtColor(matrix_.getWorkMat(),matrix_.getWorkMat(),CV_BGR2HSV);
    }

    cv::setMouseCallback(matrix_.getNameWorkMat(),[](int event, int x, int y, int, void* param) {
        if(event == cv::EVENT_LBUTTONDOWN) {
            FindColors* mainObj = static_cast<FindColors*>(param);
            if(mainObj->controlClick(y,x)) {
                mainObj->getXyPoints().setXy(std::pair<int,int>(y,x));
                FindColors::controlClick_ = true;
            }
        }
    },this);

    //Blok do znajdywania kontrolnych punktów
    if(ui->radioButtonPhoto->isChecked()) {
        if(FindColors::controlClick_) {
            FindColors::controlClick_ = false;

            //ustawiamy kolor pierwszego pixela
            color_->doColorFirstPixel(points_.getXy(),matrix_.getWorkMat());
            //ustawiamy średni kolor dla pierwszego kwadrata
            color_->doMeanColorFirstSquare(points_.getXy(),sizeSquare_,matrix_.getWorkMat());
            //Zapisz w interface
            setAllValueInInterface();
            //Znajduje pierwsze pole i liczy średni kolor tego pola
            findFirstArea(points_.getXy());
            //Ustawia zmiany do interfejsu
            setAllValueInInterface();
            //szukam wszystkie punkty
            findAllPoints();

            //Robię obrazek z kolorem
            matrix_.setPictureMat(matrix_.getWorkMat());
            draw<cv::Vec3b>(points_.getXyGroupPairs(),matrix_.getPictureMat(),color_->markColor());

            //Robię maskę tej matrycy (przez cMask nie sposób)
            matrix_.setMaskMat(cv::Mat(size_.rheight(),size_.rwidth(),CV_8UC1,cv::Scalar(0,0,0)));
            draw<uchar>(points_.getXyGroupPairs(),matrix_.getMaskMat(),static_cast<uchar>(255));

            //Wyrysowuję dwie matrycy
            if(ui->radioButtonHSV->isChecked()) {
                cv::cvtColor(matrix_.getPictureMat(),matrix_.getPictureMat(),CV_HSV2BGR);
            }
            cv::imshow(matrix_.getNameMaskMat(),matrix_.getMaskMat());
            cv::imshow(matrix_.getNamePictureMat(),matrix_.getPictureMat());

            //Czyszczę maskę i grupy punktów
            points_.getXyGroupPairs().clear();
            cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));
        }
    } else if(ui->radioButtonInRun->isChecked()) {
        if(FindColors::controlClick_) {
            FindColors::controlClick_ = false;
            //ustawiamy kolor pierwszego pixela
            color_->doColorFirstPixel(points_.getXy(),matrix_.getWorkMat());
            //ustawiamy średni kolor dla pierwszego kwadrata
            color_->doMeanColorFirstSquare(points_.getXy(),sizeSquare_,matrix_.getWorkMat());
            //Zapisz w interface
            setAllValueInInterface();
            //Znajduje punkty do pierwszego pole i liczy średni kolor tego pola
            findFirstArea(points_.getXy());
            //Ustawia zmiany do interfejsu
            setAllValueInInterface();
        }
        //szukam wszystkie punkty
        findAllPoints();
        draw<cv::Vec3b>(points_.getXyGroupPairs(),matrix_.getWorkMat(),color_->markColor());

        //Robię maskę tej matrycy (przez cMask nie sposób)
        matrix_.setMaskMat(cv::Mat(size_.rheight(),size_.rwidth(),CV_8UC1,cv::Scalar(0,0,0)));
        draw<uchar>(points_.getXyGroupPairs(),matrix_.getMaskMat(),static_cast<uchar>(255));

        cv::imshow(matrix_.getNameMaskMat(),matrix_.getMaskMat());

        //Czyszczę maskę i grupy punktów
        points_.getXyGroupPairs().clear();
        cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));

    } else {
        std::cerr << "Nie zaznaczono żadnego Modu" << std::endl;
        exit(EXIT_FAILURE);
    }
    //Po wyjściu mamy kontrolne punkty, wystarczy tylko zaznaczyć na mapie

    if(ui->radioButtonHSV->isChecked()) {
        cv::cvtColor(matrix_.getWorkMat(),matrix_.getWorkMat(),CV_HSV2BGR);
    }

    cv::imshow(matrix_.getNameWorkMat(),matrix_.getWorkMat());
}

void FindColors::findAllPoints() {
    for(int row = sizeSquare_.plusHalfSize_; row <= (size_.rheight() - sizeSquare_.minusHalfSize_); row += sizeSquare_.size_) {
        for(int col = sizeSquare_.plusHalfSize_; col <= (size_.rwidth() - sizeSquare_.minusHalfSize_); col += sizeSquare_.size_) {
            findArea(std::pair<int,int>(row,col));
        }
    }
}

template<typename T>
void FindColors::drawOneSquare(const std::pair<int,int>& yx, cv::Mat& mat, T color) {
    for(int row = yx.first - sizeSquare_.plusHalfSize_; row <= yx.first + sizeSquare_.plusHalfSize_; ++row) {
        for(int col = yx.second - sizeSquare_.plusHalfSize_; col <= yx.second + sizeSquare_.plusHalfSize_; ++col) {
            mat.at<T>(row,col) = color;
        }
    }
}

template<typename T>
void FindColors::draw(const std::vector<std::vector<std::pair<int,int>>>& groupsYX, cv::Mat& mat, T color) {
    for(const std::vector<std::pair<int,int>>& pairs : groupsYX) {
        for(const std::pair<int,int>& p : pairs) {
            drawOneSquare<T>(p,mat,color);
        }
    }
}

void FindColors::setSizeImg(const QSize& size) {
    size_ = size;
}

QSize& FindColors::getSizeImg() {
    return size_;
}

XyPoints& FindColors::getXyPoints() {
    return points_;
}

bool FindColors::controlClick(int y, int x) {
    if(y < sizeSquare_.plusHalfSize_ || y > (size_.rheight() - sizeSquare_.minusHalfSize_)) {
        return false;
    }
    if(x < sizeSquare_.plusHalfSize_ || x > (size_.rwidth() - sizeSquare_.minusHalfSize_)) {
        return false;
    }
    return true;
}

bool FindColors::isPointBelongsToField(const std::pair<int,int>& yx) {
    if(yx.first < sizeSquare_.plusHalfSize_ || yx.first > (size_.rheight() - sizeSquare_.minusHalfSize_)) {
        return false;
    }
    if(yx.second < sizeSquare_.plusHalfSize_ || yx.second > (size_.rwidth() - sizeSquare_.minusHalfSize_)) {
        return false;
    }
    return true;
}

void FindColors::wholeCheckingFirst(const std::pair<int, int>& tmpYX, std::queue<std::pair<int,int>>& queue) {
    if(isPointBelongsToField(tmpYX)) {
        if(!hasTrueElementsInSquare(tmpYX)) {
            setTrueElementsOfMask(tmpYX);
            cv::Vec3b tmpColor = color_->doMeanColorTmpSquare(tmpYX,sizeSquare_.size_,matrix_.getWorkMat());
            if(color_->compareColorOfNextSquare(tmpColor)) {
                color_->addColor(tmpColor);
                queue.push(tmpYX);
                points_.getXyPairs().push_back(tmpYX);
            }
        }
    }
}

void FindColors::wholeChecking(const std::pair<int, int>& tmpYX, std::queue<std::pair<int,int>>& queue) {
    if(isPointBelongsToField(tmpYX)) {
        if(!hasTrueElementsInSquare(tmpYX)) {
            setTrueElementsOfMask(tmpYX);
            cv::Vec3b tmpColor = color_->doMeanColorTmpSquare(tmpYX,sizeSquare_.size_,matrix_.getWorkMat());
            if(ui->radioButtonArea->isChecked()) {
                if(color_->compareColorOfNextArea(tmpColor)) {
                    queue.push(tmpYX);
                    points_.getXyPairs().push_back(tmpYX);
                }
            } else if(ui->radioButtonSquare->isChecked()) {
                if(color_->compareColorOfNextSquare(tmpColor)) {
                    queue.push(tmpYX);
                    points_.getXyPairs().push_back(tmpYX);
                }
            } else {
                std::cout << "There are not checked: Area or Square" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void FindColors::findFirstArea(const std::pair<int,int>& yx) { // yx tu jest zawsze w granicach pola
    std::queue<std::pair<int,int>> queue;
    queue.push(yx);
    setTrueElementsOfMask(yx);
    points_.getXyPairs().push_back(yx);
    std::pair<int,int> tmpYX;
    while(!queue.empty()) {
        std::pair<int,int> current = queue.front();
        queue.pop();

        //Sprwdzamy 8 sąsiednie kwadraty

        //górny
        tmpYX = std::pair<int,int>(current.first - sizeSquare_.size_,current.second);
        wholeCheckingFirst(tmpYX,queue);

        //prawy
        tmpYX = std::pair<int,int>(current.first,current.second + sizeSquare_.size_);
        wholeCheckingFirst(tmpYX,queue);

        //dolny
        tmpYX = std::pair<int,int>(current.first + sizeSquare_.size_,current.second);
        wholeCheckingFirst(tmpYX,queue);

        //lewy
        tmpYX = std::pair<int,int>(current.first,current.second - sizeSquare_.size_);
        wholeCheckingFirst(tmpYX,queue);

        //górny-prawy
        tmpYX = std::pair<int,int>(current.first - sizeSquare_.size_,current.second + sizeSquare_.size_);
        wholeCheckingFirst(tmpYX,queue);

        //dolny-prawy
        tmpYX = std::pair<int,int>(current.first + sizeSquare_.size_,current.second + sizeSquare_.size_);
        wholeCheckingFirst(tmpYX,queue);

        //dolny-lewy
        tmpYX = std::pair<int,int>(current.first + sizeSquare_.size_,current.second - sizeSquare_.size_);
        wholeCheckingFirst(tmpYX,queue);

        //górny-lewy
        tmpYX = std::pair<int,int>(current.first - sizeSquare_.size_,current.second - sizeSquare_.size_);
        wholeCheckingFirst(tmpYX,queue);
    }
    points_.getXyGroupPairs().push_back(points_.getXyPairs());
    color_->doMeanColorFirstArea(points_.getXyPairs().size());

    //Czyścimy wektor par
    points_.getXyPairs().clear();
}

void FindColors::findArea(const std::pair<int,int>& yx) { // yx tu jest zawsze w granicach pola
    std::queue<std::pair<int,int>> queue;
    //queue.push(yx);
    //setTrueElementsOfMask(yx);
    //points_.getXyPairs().push_back(yx);
    wholeChecking(yx,queue);
    std::pair<int,int> tmpYX;
    while(!queue.empty()) {
        std::pair<int,int> current = queue.front();
        queue.pop();

        //Sprwdzamy 8 sąsiednie kwadraty

        //górny
        tmpYX = std::pair<int,int>(current.first - sizeSquare_.size_,current.second);
        wholeChecking(tmpYX,queue);

        //prawy
        tmpYX = std::pair<int,int>(current.first,current.second + sizeSquare_.size_);
        wholeChecking(tmpYX,queue);

        //dolny
        tmpYX = std::pair<int,int>(current.first + sizeSquare_.size_,current.second);
        wholeChecking(tmpYX,queue);

        //lewy
        tmpYX = std::pair<int,int>(current.first,current.second - sizeSquare_.size_);
        wholeChecking(tmpYX,queue);

        //górny-prawy
        tmpYX = std::pair<int,int>(current.first - sizeSquare_.size_,current.second + sizeSquare_.size_);
        wholeChecking(tmpYX,queue);

        //dolny-prawy
        tmpYX = std::pair<int,int>(current.first + sizeSquare_.size_,current.second + sizeSquare_.size_);
        wholeChecking(tmpYX,queue);

        //dolny-lewy
        tmpYX = std::pair<int,int>(current.first + sizeSquare_.size_,current.second - sizeSquare_.size_);
        wholeChecking(tmpYX,queue);

        //górny-lewy
        tmpYX = std::pair<int,int>(current.first - sizeSquare_.size_,current.second - sizeSquare_.size_);
        wholeChecking(tmpYX,queue);
    }
    points_.getXyGroupPairs().push_back(points_.getXyPairs());

    //Czyścimy wektor par
    points_.getXyPairs().clear();
}

bool FindColors::hasTrueElementsInSquare(const std::pair<int, int>& yx) {
    for(int row = yx.first - sizeSquare_.plusHalfSize_; row <= yx.first + sizeSquare_.plusHalfSize_; ++row) {
        for(int col = yx.second - sizeSquare_.plusHalfSize_; col <= yx.second + sizeSquare_.plusHalfSize_; ++col) {
            if(cMask_[row][col] == 1) {
                return true;
            }
        }
    }
    return false;
}

void FindColors::setTrueElementsOfMask(const std::pair<int,int>& yx) {
    for(int row = yx.first - sizeSquare_.plusHalfSize_; row <= yx.first + sizeSquare_.plusHalfSize_; ++row) {
        for(int col = yx.second - sizeSquare_.plusHalfSize_; col <= yx.second + sizeSquare_.plusHalfSize_; ++col) {
            cMask_[row][col] = 1;
        }
    }
}
