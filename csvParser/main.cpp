#include <iostream>
#include <tuple>
#include "CsvParser.h"
#include "TuplePrinter.h"

int main(int argc, char **argv) {
    std::ifstream inputFile;
    // first argument -- file
    if (argc > 1) {
        inputFile.open(argv[1], std::ios::binary);
        if (!inputFile.is_open()){
            std::cout << "Can not open file!";
            return EXIT_FAILURE;
        }
    } else {
        std::cout << "Enter file name";
        return EXIT_FAILURE;
    }
    // second -- number of lines to skip
    int skipLines;
    if (argc > 2) {
        skipLines = std::stoi(argv[2]);
    } else {
        skipLines = 0; // setting default value of skipped lines
    }

    CsvParser<int, std::string, double> parser(inputFile, skipLines, ';');
    for (auto &rs : parser) {
        std::cout << rs << std::endl;
    }

    return 0;
}