#ifndef SIZESQUARE_H
#define SIZESQUARE_H

class SizeSquare {
public:
    SizeSquare(int sizeSquare = 0);
    ~SizeSquare();
    void setNewSize(int size);

    int size_;
    int minusHalfSize_;
    int plusHalfSize_;
};

#endif // SIZESQUARE_H
