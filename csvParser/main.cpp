#include <iostream>
#include <tuple>
#include <fstream>
#include "CsvParser.h"
#include "TuplePrinter.h"

int main(int argc, char **argv) {
    int skipLines;
    if (argc > 1) {
        skipLines = std::stoi(argv[1]);
    } else {
        skipLines = 0; // setting default value of skipped lines
    }
    std::ifstream inputFile("test.csv");
    if (!inputFile.is_open()){
        std::cout << "Can not open file!";
        return -1;
    }

    CsvParser<int, std::string, double> parser(inputFile, skipLines, ';');
    for (auto &rs : parser) {
        std::cout << rs << std::endl;
    }

    return 0;
}