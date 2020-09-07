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
    auto it = wordMap.begin(); // use auto to declare iterators auto==std::map <std::string, int> :: iterator
    for (int i = 0; it != wordMap.end(); it++, i++) {  // выводим их
        std::cout << "  Key:  " << it->first << " Value:  " << it->second << std::endl;
    }
    return this->wordCounter;
}

void WordCounter::writeCsv(const std::string &outputFileName) const {

    std::list<std::pair<int, std::string>> items;
    auto it = wordMap.begin(); // use auto to declare iterators auto==std::map <std::string, int> :: iterator
    for (int i = 0; it != wordMap.end(); it++, i++) {  // выводим их
        items.emplace_back(it->second, it->first);
    }
    items.sort();

    auto itt = items.begin(); // use auto to declare iterators auto==std::map <std::string, int> :: iterator
    for (int i = 0; itt != items.end(); itt++, i++) {  // выводим их
        std::cout << "  Key:  " << itt->first << " Value:  " << itt->second << std::endl;
    }

    std::ofstream outputStream(outputFileName);
}
