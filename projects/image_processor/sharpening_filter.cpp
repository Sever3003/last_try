#include "sharpening_filter.h"

const Matrix SHARP_MATRIX = {{0,  -1, 0},
                             {-1, 5,  -1},
                             {0,  -1, 0}};

Sharpening::Sharpening() : Matrix(SHARP_MATRIX) {}

