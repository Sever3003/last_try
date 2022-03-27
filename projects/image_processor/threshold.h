#pragma once

#include "image.h"
#include "filter.h"

class Threshold : public Filter {
public:
    Threshold(double threshold);

    Image Apply(const Image &image) const override;

private:
    double threshold_;
};
