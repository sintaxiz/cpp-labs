#include "WordCounter.h"

#include <iostream>
#include <string>

// wordCounter -- class
// работа с файлами в С++?
// ключ - значение (слово - количество)
// using namespace - раскрывает видимость namespace

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