#pragma once

#include <cstdint>
#include <vector>

struct Pixel {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
};

const Pixel BLACK = {0, 0, 0};
const Pixel WHITE = {255, 255, 255};