#include "findcolors.h"
#include "ui_findcolors.h"

bool FindColors::controlClick_ = false;

FindColors::FindColors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FindColors), sizeSquare_(5) // tylko nieparzyste
{
    ui->setupUi(this);
    defaultStyles();

    //cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));
}

FindColors::~FindColors() {
    delete ui;
    delete color_;
}

void FindColors::processVideo() {
    video_.getVideoCapture()->read(matrix_.getWorkMat());

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
            std::cout << points_.getXy().first << " | " << points_.getXy().second << std::endl;
            FindColors::controlClick_ = false;

            //ustawiamy kolor pierwszego pixela
            color_->doColorFirstPixel(points_.getXy(),matrix_.getWorkMat());
            //średni kolor dla color dla pierwszego kwadrata
            color_->doMeanColorFirstSquare(points_.getXy(),sizeSquare_,matrix_.getWorkMat());
            //Zapisz w interface
            ui->lcdNumberOneS->display(color_->getColorSquare()[0]);
            ui->lcdNumberTwoS->display(color_->getColorSquare()[1]);
            ui->lcdNumberThreeS->display(color_->getColorSquare()[2]);

            findFirstArea(points_.getXy());

            matrix_.setPictureMat(matrix_.getWorkMat());
            draw(points_.getXyGroupPairs(),matrix_.getPictureMat());
            //drawOneSquare(points_.getXy(),matrix_.getPictureMat());
            cv::imshow(matrix_.getNamePictureMat(),matrix_.getPictureMat());

            //Czyszczę maskę i grupy punktów
            points_.getXyGroupPairs().clear();
            cMask_ = std::vector<std::vector<int>>(size_.rheight(), std::vector<int>(size_.rwidth(),0));
        }
    } else if(ui->radioButtonInRun->isChecked()) {

    } else {
        std::cerr << "Nie zaznaczono żadnego Modu" << std::endl;
        exit(EXIT_FAILURE);
    }
    //Po wyjściu mamy kontrolne punkty, wystarczy tylko zaznaczyć na mapie

    cv::imshow(matrix_.getNameWorkMat(),matrix_.getWorkMat());
}

void FindColors::drawOneSquare(const std::pair<int,int>& yx, cv::Mat& mat) {
    for(int row = yx.first - sizeSquare_.plusHalfSize_; row <= yx.first + sizeSquare_.plusHalfSize_; ++row) {
        for(int col = yx.second - sizeSquare_.plusHalfSize_; col <= yx.second + sizeSquare_.plusHalfSize_; ++col) {
            mat.at<cv::Vec3b>(row,col) = cv::Vec3b(0,0,255);
        }
    }
}

void FindColors::draw(const std::vector<std::vector<std::pair<int,int>>>& groupsYX, cv::Mat& mat) {
    for(const std::vector<std::pair<int,int>>& pairs : groupsYX) {
        for(const std::pair<int,int>& p : pairs) {
            drawOneSquare(p,mat);
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

void FindColors::wholeChecking(const std::pair<int, int>& tmpYX, std::queue<std::pair<int,int>>& queue) {
    if(isPointBelongsToField(tmpYX)) {
        if(!hasTrueElementsInSquare(tmpYX)) {
            setTrueElementsOfMask(tmpYX);
            cv::Vec3b tmpColor = color_->doMeanColorTmpSquare(tmpYX,sizeSquare_.size_,matrix_.getWorkMat());
            if(color_->compareColorOfNextSquare(tmpColor)) {

                queue.push(tmpYX);
                //yxPairs.push_back(tmpYX);
                points_.getXyPairs().push_back(tmpYX);
            }
        }
    }
}

void FindColors::findFirstArea(const std::pair<int, int>& yx) { // yx tu jest zawsze w granicach pola
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

















