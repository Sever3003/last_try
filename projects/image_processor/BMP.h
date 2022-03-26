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
    void Read(const std::string &input_file_name);

    void Apply(const Filter &filter);

    void Write(const std::string &output_file_name);

    class InvalidFileError : public std::exception {};
    class OpeningFileError : public std::exception {};


private:
    std::array<uint8_t, HEADER_SIZE> header_;
    Image image_;

};

