#include "BMP.h"
#include <iostream>
#include <fstream>

static const size_t WIDTH_BYTE = 18;
static const size_t HEIGHT_BYTE = 22;
static const size_t FILE_SIZE_BYTE = 2;

void BMP::Apply(const Filter &filter) {
    image_ = filter.Apply(image_);
}


void BMP::Read(const std::string &input_file_name) {
    std::ifstream fin;
    fin.open(input_file_name, std::ios::binary);
    if (fin) {
        fin.read(reinterpret_cast<char *>(header_.data()), sizeof(uint8_t) * HEADER_SIZE);
        if (fin.gcount() != HEADER_SIZE) {
            throw InvalidFileError();
        }
        int width = *(reinterpret_cast<int *>(header_.data() + WIDTH_BYTE));
        int height = *(reinterpret_cast<int *>(header_.data() + HEIGHT_BYTE));
        if (width <= 0) {
            throw InvalidFileError();
        }
        bool minus = false;
        if (height <= 0) {
            minus = true;
        }
        Image body(height, width);
        for (size_t i = 0; i < abs(height); ++i) {
            for (size_t j = 0; j < width; ++j) {
                Pixel pixel{};
                if (fin.eof()) {
                    throw InvalidFileError();
                }
                fin.read(reinterpret_cast<char *>(&pixel.blue), sizeof(uint8_t));
                fin.read(reinterpret_cast<char *>(&pixel.green), sizeof(uint8_t));
                fin.read(reinterpret_cast<char *>(&pixel.red), sizeof(uint8_t));
                if (minus) {
                    body.At(height + i, j) = pixel;
                } else {
                    body.At(height - 1 - i, j) = pixel;
                }
            }
        }
        image_ = body;
        fin.close();
    } else {
        throw OpeningFileError();
    }
}


void BMP::Write(const std::string &output_file_name) {
    *(reinterpret_cast<int *>(header_.data() + HEIGHT_BYTE)) = image_.Height();
    *(reinterpret_cast<int *>(header_.data() + WIDTH_BYTE)) = image_.Width();
    *(reinterpret_cast<int *>(header_.data() + FILE_SIZE_BYTE)) =
            image_.Height() * image_.Width() * sizeof(Pixel) + HEADER_SIZE;
    std::ofstream fout;
    fout.open(output_file_name, std::ios::binary);
    if (fout) {
        fout.write(reinterpret_cast<const char *>(header_.data()), sizeof(uint8_t) * HEADER_SIZE);
        for (size_t i = 0; i < image_.Height(); ++i) {
            for (size_t j = 0; j < image_.Width(); ++j) {
                fout.write(reinterpret_cast<const char *>(&image_.At(image_.Height() - 1 - i, j)), sizeof(Pixel));
            }
        }
        fout.close();
    } else {
        std::cout << "File did not open" << std::endl;
    }
}
