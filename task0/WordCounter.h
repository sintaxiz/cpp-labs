#pragma once

#include <map>
#include <string>

class WordCounter {
private:
    std::map<std::string, int> wordMap;
    int wordCounter;
public:
    WordCounter() {
        wordCounter = 0;
    }

    void addFile(const std::string &inputFileName); // распарсить файл и проинициализировать переменные

    void writeCsv(const std::string &outputFileName) const; // отсортировать и вывести с процентами

};
