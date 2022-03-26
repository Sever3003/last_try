#include "gaussian_blur_filter.h"


Matrix GaussMatrix(double sigma){
    int step = sigma;
    size_t matrix_size = 3 * sigma;
    if (step % 2 == 0){
        ++matrix_size;
    }
    Matrix::MatrixBody gausian_body(matrix_size, std::vector<double>(matrix_size));

    double sum = 0;
    for (int x = -step; x <= step; ++x) {
        for (int y = -step; y <= step; ++y) {
            double distance = x * x + y * y;
            gausian_body[x + step][y + step] = (exp(-(distance * distance) / sigma)) / (M_PI * sigma);
            sum += gausian_body[x + step][y + step];

        }
    }
    for (int x = -step; x <= step; ++x) {
        for (int y = -step; y <= step; ++y) {
            gausian_body[x + step][y + step] /= sum;
        }
    }
    return gausian_body;
}

GaussianBlur::GaussianBlur(double sigma): Matrix(std::move(GaussMatrix(sigma))){}
