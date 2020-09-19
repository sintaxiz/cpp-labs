#include "WordCounter.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <list>
#include <exception>

class FileException : public std::exception {
    const char *what() const throw() {
        return "Can not open file";
    }
};

std::string parseWord(const std::string &word) {
    std::string newWord;
    for (char ch : word) {
        if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            newWord.push_back(ch);
        }
    }
    return newWord;
}

void WordCounter::addFile(const std::string &inputFileName) {

    std::fstream input(inputFileName);
    if (!input) {
        throw FileException();
    }

    std::stringstream textStream;
    textStream << input.rdbuf();
    std::string rawWord;
    while (textStream >> rawWord) {
        std::string newWord = parseWord(rawWord);
        if (newWord.empty()) {
            continue;
        }
        wordCounter++;
        wordMap[newWord]++;
    }
}

void writeLine(const std::pair<int, std::string> &item, std::ofstream &outputStream, int wordCounter) {
    outputStream << item.second << ','
                 << item.first << ','
                 << ((double) item.first) / wordCounter * 100 << '%' << std::endl;
}

void WordCounter::writeCsv(const std::string &outputFileName) const {

    std::ofstream outputStream(outputFileName);
    if (!outputStream) {
        throw FileException();
    }

    // Using list to sort Data
    std::list<std::pair<int, std::string>> wordList;
    // Filling & sorting list
    for (const auto &pair : wordMap) {
        wordList.emplace_back(pair.second, pair.first);
    }
    wordList.sort();

    for (auto const &word : wordList) {
        writeLine(word, outputStream, wordCounter);
    }
    outputStream.close();
}
