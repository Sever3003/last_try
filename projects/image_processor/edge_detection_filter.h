#pragma once
#include "matrix.h"
#include "grayscale_filter.h"
#include "threshold.h"

class EdgeDetection : public Matrix{
public:
    EdgeDetection(double threshold);

    Image Apply(const Image &image) const override;
private:
    double threshold_;

};

