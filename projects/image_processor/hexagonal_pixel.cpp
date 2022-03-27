#include "hexagonal_pixel.h"

Matrix::MatrixBody CreateHexagon(int radius) {
    Matrix::MatrixBody hexagonal_body(radius * 2 + 1, std::vector<double>(radius * 2 + 1, 0));
    int64_t sum = 0;
    int third_part = (hexagonal_body.size() / 3);
    int half = (hexagonal_body.size() / 2);
    for (size_t i = 0; i < third_part; ++i) {
        for (size_t j = half - 1.5 * i; j < half + 1.5 * i; ++j) {
            hexagonal_body[i][j] = 255;
            sum += 255;
        }
    }
    for (size_t i = third_part; i < 2 * third_part; ++i) {
        for (size_t j = 0; j < hexagonal_body.size(); ++j) {
            hexagonal_body[i][j] = 255;
            sum += 255;
        }
    }
    for (int i = 0; i < third_part; ++i) {
        for (int j = 1.5 * i; j < hexagonal_body.size() - 1.5 * i; ++j) {
            hexagonal_body[i + 2 * third_part][j] = 255;
            sum += 255;
        }
    }
    for (size_t i = 0; i < hexagonal_body.size(); ++i) {
        for (size_t j = 0; j < hexagonal_body[0].size(); ++j) {
            hexagonal_body[i][j] = hexagonal_body[i][j] / sum;
        }
    }
    return hexagonal_body;
}

HexagonPath::HexagonPath(const Matrix::MatrixBody &body) : hexagon_body(body) {};

int HexagonPath::Radius() const {
    return (hexagon_body.size() - 1) / 2;
}


void HexagonPath::Apply(Image &image, int x, int y) const {
    double blue = 0;
    double green = 0;
    double red = 0;
    int size = (hexagon_body.size() - 1) / 2;
    for (int i = -size; i <= size; ++i) {
        for (int j = -size; j <= size; ++j) {

            auto pixel = image.At(x + j, y + i);
            blue += static_cast<double>(pixel.blue) * hexagon_body[size + i][size + j];
            green += static_cast<double>(pixel.green) * hexagon_body[size + i][size + j];
            red += static_cast<double>(pixel.red) * hexagon_body[size + i][size + j];
        }
    }
    Pixel result_pixel = {static_cast<uint8_t>(blue), static_cast<uint8_t>(green), static_cast<uint8_t>(red)};
    for (int i = -size; i <= size; ++i) {
        for (int j = -size; j <= size; ++j) {
            if (hexagon_body[size + i][size + j] != 0) {
                image.At(x + j, y + i) = result_pixel;
            }
        }
    }
}

Hexagonal::Hexagonal(int radius) : hex_(CreateHexagon(radius)) {};

Image Hexagonal::Apply(const Image &image) const {
    int i = 0;
    auto result = image;
    while (i < image.Height()) {
        int j = 0;
        while (j < image.Width()) {
            hex_.Apply(result, j, i);
            j += hex_.Radius() * 2;
        }
        i += 2 * hex_.Radius();
    }
    i = hex_.Radius();
    while (i < image.Height()) {
        int j = hex_.Radius();
        while (j < image.Width()) {
            hex_.Apply(result, j, i);
            j += hex_.Radius() * 2;
        }
        i += 2 * hex_.Radius();
    }
    return result;
}