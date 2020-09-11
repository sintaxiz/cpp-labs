#include "WordCounter.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
     if (argc < 3) {
         std::cout << "No data" << std::endl;
         return 0;
     }
    WordCounter wc;
    wc.addFile(argv[1]);
    wc.writeCsv(argv[2]);
    return 0;
}