#include "edge_detection_filter.h"
#include "threshold.h"


const Matrix EDGE_DETECTION_MATRIX = {{0,  -1, 0},
                                      {-1, 4,  -1},
                                      {0,  -1, 0}};

EdgeDetection::EdgeDetection(double threshold) : Matrix(EDGE_DETECTION_MATRIX), threshold_(threshold) {}

Image EdgeDetection::Apply(const Image &image) const {
    auto image_result = Grayscale().Apply(image);
    image_result = Matrix::Apply(image_result);
    return Threshold(threshold_).Apply(image_result);
}
