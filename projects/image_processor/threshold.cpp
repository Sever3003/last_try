#include "threshold.h"
#include "pixel.h"

Threshold::Threshold(double threshold) : threshold_(threshold) {}

Image Threshold::Apply(const Image &image) const {
    auto image_result = image;
    for (size_t i = 0; i < image_result.Height(); ++i) {
        for (size_t j = 0; j < image_result.Width(); ++j) {
            auto pixel = image_result.At(i, j);
            if ((static_cast<int>(pixel.blue)) <
                threshold_ * 255) {
                image_result.At(i, j) = BLACK;
            } else {
                image_result.At(i, j) = WHITE;
            }
        }
    }
    return image_result;
}