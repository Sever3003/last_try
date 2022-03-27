#include "image.h"

Image::Image(ImageBody &&body) : body_(std::move(body)) {}

Image::Image(const ImageBody &body) : body_(body) {}

const Pixel &Image::At(int64_t x, int64_t y) const {
    int correct_y = std::max(static_cast<int64_t>(0), std::min(x, static_cast<int64_t>(body_.size()) - 1));
    int correct_x = std::max(static_cast<int64_t>(0), std::min(y, static_cast<int64_t>(body_[0].size()) - 1));
    return body_[correct_y][correct_x];
}

size_t Image::Height() const {
    return body_.size();
}

size_t Image::Width() const {
    return body_[0].size();
}

void Image::CutLastColumn() {
    for (auto &row: body_) {
        row.pop_back();
    }
}

void Image::CutLastRow() {
    body_.pop_back();
}

Pixel &Image::At(int64_t x, int64_t y) {
    int correct_y = std::max(static_cast<int64_t>(0), std::min(x, static_cast<int64_t>(body_.size()) - 1));
    int correct_x = std::max(static_cast<int64_t>(0), std::min(y, static_cast<int64_t>(body_[0].size()) - 1));
    return body_[correct_y][correct_x];
}

Image::Image(int64_t height, int64_t width) : body_(ImageBody(height, std::vector<Pixel>(width))) {}