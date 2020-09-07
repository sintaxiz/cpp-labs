#include "WordCounter.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <list>

int WordCounter::addFile(const std::string &fileName) {

    std::fstream myStream;
    myStream.open(fileName);

    std::stringstream ss;
    ss << myStream.rdbuf();

    std::string word;
    while (ss >> word) {
        wordCounter++;
        wordMap[word]++;
    }

    return this->wordCounter;
}

void WordCounter::writeCsv(const std::string &outputFileName) const {

    // Using list to sort Data
    std::list<std::pair<int, std::string>> items;
    // Filling & sorting list
    for (const auto &pair : wordMap) {
        items.emplace_back(pair.second, pair.first);
    }
    items.sort();

    std::ofstream outputStream(outputFileName);
    while (!(items.empty())) {
        std::pair<int, std::string> item = items.back();
        outputStream << item.second << ','
                     << item.first << ','
                     << ((double) item.first) / wordCounter * 100 << '%' << std::endl;
        items.pop_back();
    }
    outputStream.close();
}
