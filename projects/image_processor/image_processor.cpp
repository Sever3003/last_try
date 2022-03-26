#include "image_processor.h"

#include <cmath>
#include "crop_filter.h"
#include <cstdio>

void Reference() {
    std::cout << "-crop need 2 arguments: width, height. Сrops the image in width and height" << std::endl;
    std::cout << "-blur need 1 argument: sigma. Applies a Gaussian blur with a value of sigma to the image"
              << std::endl;
    std::cout << "-gs no arguments needed. Applies grayscale to the image" << std::endl;
    std::cout << "-sharp no arguments needed. Sharpens the image" << std::endl;
    std::cout << "-negative no arguments needed. Сonverts the image to a negative" << std::endl;
    std::cout
            << "-edge need 1 argument: threshold. The image is converted to grayscale, and then the borders are highlighted"
            << std::endl;
    std::cout << "-hexagon need 1 argument: radius. Turns an image into hexagonal shapes with a radius" << std::endl;
}

bool WrongArgumentsForFilter(std::string filter, int argc, int i, int need_arg) {
    if (argc - i <= need_arg) {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Reference();
        return 0;
    }

    if (argc < 3) {
        std::cout << "Not enough arguments, see help:" << std::endl;
        Reference();
        return 0;
    }

    std::string input_address = argv[1];
    BMP bmp;
    bmp.Read(input_address);
    std::string output_file(argv[2]);

    for (int i = 3; i < argc; ++i) {
        std::string command(argv[i]);

        if (command == "-crop") {
            if (!WrongArgumentsForFilter("-crop", argc, i, 2)) {
                return 0;
            }
            int64_t width = std::stoll(argv[i + 1]);
            int64_t height = std::stoll(argv[i + 2]);
            bmp.Apply(Crop(static_cast<size_t>(height), static_cast<size_t>(width)));
            i += 2;

        } else if (command == "-blur") {
            if (!WrongArgumentsForFilter("-blur", argc, i, 1)) {
                return 0;
            }
            double sigma = std::stod(argv[i + 1]);
            if (sigma < 0) {
                throw std::invalid_argument("Incorrect arguments for -blur");
            }
            bmp.Apply(GaussianBlur(sigma));
            i += 1;
        } else if (command == "-gs") {
            bmp.Apply(Grayscale());
        } else if (command == "-sharp") {
            bmp.Apply(Sharpening());
        } else if (command == "-negative") {
            bmp.Apply(Negative());
        } else if (command == "-edge") {
            if (!WrongArgumentsForFilter("-edge", argc, i, 1)) {
                return 0;
            }
            double threshold = std::stod(argv[i + 1]);
            if (threshold < 0 || threshold > 1) {
                throw std::invalid_argument("Incorrect arguments for -edge, expected value from 0 to 1");
            }
            bmp.Apply(EdgeDetection(threshold));
            i += 1;
        } else if (command == "-hexagon") {
            if (!WrongArgumentsForFilter("-hexagon", argc, i, 1)) {
                return 0;
            }
            int radius = std::stoi(argv[i + 1]);
            if (radius <= 0) {
                throw std::invalid_argument("Incorrect arguments for -hexagon, enter radius > 0");
            }
            bmp.Apply(Hexagonal(radius));
            i += 1;
        }
    }
    bmp.Write(output_file);
    return 0;
}
//int main(int argc, char *argv[]) {
//    BMP bmp;
//    bmp.Read("../examples/example.bmp");
//    bmp.Apply(Grayscale());
//    bmp.Write("../examples/example2.bmp");
//}