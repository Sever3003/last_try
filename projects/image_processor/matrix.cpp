#include "matrix.h"

Matrix::Matrix(const MatrixBody &matrix_body) : body_(matrix_body) {}

#include <iostream>

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> &other) {
    size_t i = 0;
    body_.resize(other.size());
    for (const auto &row: other) {
        body_[i].reserve(row.size());
        for (const auto &elem: row) {
            body_[i].push_back(elem);
        }
        ++i;
    }
}

Image Matrix::Apply(const Image &image) const {
    Image image_result = image;
    int height = body_.size() / 2;
    int width = body_[0].size() / 2;

    for (int i = 0; i < image.Height(); ++i) {
        for (int j = 0; j < image.Width(); ++j) {
            double green = 0;
            double red = 0;
            double blue = 0;
            Pixel current;
            int current_height;
            int current_width;
            for (int coef_i = -1 * height; coef_i <= 1 * height; ++coef_i) {
                for (int coef_j = -1 * width; coef_j <= 1 * width; ++coef_j) {
                    current = image.At(i + coef_i, j + coef_j);
                    current_height = coef_i + height;
                    current_width = coef_j + width;
                    green += body_[current_height][current_width] *
                             static_cast<double>(current.green);
                    red += body_[current_height][current_width] *
                           static_cast<double>(current.red);
                    blue += body_[current_height][current_width] *
                            static_cast<double>(current.blue);
                }
            }
            Pixel pixel = {static_cast<uint8_t>(blue), static_cast<uint8_t>(green), static_cast<uint8_t>(red)};
            image_result.At(i, j) = pixel;
        }
    }
    return image_result;
}


Matrix &Matrix::operator=(const MatrixBody &body) {
    body_ = body;
    return *this;
}

Matrix &Matrix::operator=(MatrixBody &&body) {
    body_ = body;
    return *this;
}