#include "WordCounter.h"

#include <iostream>

int main(int argc, char *argv[]) {
     if (argc < 3) {
         std::cout << "No data";
         return 0;
     }
    WordCounter wc;
    wc.addFile(argv[1]);
    wc.writeCsv(argv[2]);
    return 0;
}
