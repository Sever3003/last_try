//#include "../BMP.h"
//
//#include <iostream>
//#include <fstream>
//#include <filesystem>
//#include "../../contrib/catch/catch.hpp"
//const std::string INPUT_FILE = "../../examples/example.bmp";
//const std::string TEST_OUTPUT_FILE = "../../examples/test.bmp";
//const std::string PATH_INVALID_FILE = "../../examples/test.bmp";
//
//
//void CompareFile(const std::string& first, const std::string& second) {
//    std::ifstream fin_first;
//    fin_first.open(first, std::ios::binary);
//    std::ifstream fin_second;
//    fin_second.open(second, std::ios::binary);
//    REQUIRE((fin_first && fin_second));
//    while (!fin_first.eof() && !fin_second.eof()) {
//        char first_byte;
//        char second_byte;
//        fin_first.read(&first_byte, sizeof(char));
//        fin_second.read(&second_byte, sizeof(char));
//        REQUIRE(first_byte == second_byte);
//    }
//    REQUIRE((fin_first.eof() && fin_second.eof()));
//    fin_first.close();
//    fin_second.close();
//}
//
//
//TEST_CASE("TestReadWrite") {
//    BMP bmp;
//    bmp.Read(INPUT_FILE);
//    bmp.Write(TEST_OUTPUT_FILE);
//    CompareFile(INPUT_FILE, TEST_OUTPUT_FILE);
//}
//
//
//TEST_CASE("TestInvalidFile") {
//    char c = '1';
//    std::ofstream fout;
//    fout.open(PATH_INVALID_FILE, std::ios::binary);
//    for (int i = 0; i < 22; ++i) {
//        fout << c;
//    }
//    fout.close();
//    BMP bmp;
//    bool caught = false;
//    try {
//        bmp.Read(PATH_INVALID_FILE);
//    }
//    catch(BMP::InvalidFileError&){
//        caught = true;
//    }
//    REQUIRE(caught);
//}
//
//
