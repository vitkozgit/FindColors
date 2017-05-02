#include "xypoints.h"

XyPoints::XyPoints() : xy_(std::pair<int,int>(0,0)),
                       xyPairs_(std::vector<std::pair<int,int>>(0)),
                       xyGroupPairs_(std::vector<std::vector<std::pair<int,int>>>(0))
{

}

XyPoints::~XyPoints() {}

std::pair<int,int>& XyPoints::getXy() {
    return xy_;
}

std::vector<std::pair<int,int>>& XyPoints::getXyPairs() {
    return xyPairs_;
}

std::vector<std::vector<std::pair<int,int>>>& XyPoints::getXyGroupPairs() {
    return xyGroupPairs_;
}

void XyPoints::setXy(const std::pair<int,int>& xy) {
    xy_ = xy;
}
