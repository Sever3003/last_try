#pragma once

#include "matrix.h"

class HexagonPath {
private:
    Matrix::MatrixBody hexagon_body;
public:
    HexagonPath(const Matrix::MatrixBody &body);

    void Apply(Image &image, int x, int y) const;

    int Radius() const;
};

class Hexagonal : public Matrix {
public:
    Hexagonal(int radius);

    Image Apply(const Image &image) const override;

private:
    HexagonPath hex_;
};