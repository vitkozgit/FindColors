#include "sizesquare.h"

SizeSquare::SizeSquare(int sizeSquare) {
    setNewSize(sizeSquare);
}

SizeSquare::~SizeSquare() {}

void SizeSquare::setNewSize(int sizeSquare) {
    size_ = sizeSquare;
    minusHalfSize_ = (sizeSquare + 1) / 2;
    plusHalfSize_ = (sizeSquare - 1) / 2;
}
