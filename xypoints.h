#ifndef XYPOINTS_H
#define XYPOINTS_H

#include <vector>

class XyPoints {
public:
    XyPoints();
    ~XyPoints();
    std::pair<int,int>& getXy();
    std::vector<std::pair<int,int>>& getXyPairs();
    std::vector<std::vector<std::pair<int,int>>>& getXyGroupPairs();

    void setXy(const std::pair<int,int>& xy);
private:
    std::pair<int,int> xy_;
    std::vector<std::pair<int,int>> xyPairs_;
    std::vector<std::vector<std::pair<int,int>>> xyGroupPairs_;
};

#endif // XYPOINTS_H
