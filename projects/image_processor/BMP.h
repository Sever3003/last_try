#pragma once

#include "pixel.h"
#include "filter.h"
#include "matrix.h"
#include <iostream>
#include <array>

class Filter;

static const size_t HEADER_SIZE = 54;

class BMP {

public:
    Image Read(const std::string &input_file_name);


    void Write(const std::string &output_file_name, const Image &image);

    class InvalidFileError : public std::exception {
    };

    class OpeningFileError : public std::exception {
    };


private:
    std::array<uint8_t, HEADER_SIZE> header_;
};

