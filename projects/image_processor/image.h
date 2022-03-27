#pragma once

#include "pixel.h"

class Image {
public:
    using ImageBody = std::vector<std::vector<Pixel>>;

    Image() = default;

    Image(int64_t height, int64_t width);

    Image(ImageBody &&body);

    Image(const ImageBody &body);

    const Pixel &At(int64_t x, int64_t y) const;

    size_t Height() const;

    size_t Width() const;

    Image(const Image &image) = default;

    void CutLastColumn();

    void CutLastRow();

    Pixel &At(int64_t x, int64_t y);

private:
    ImageBody body_;
};