#include "Calculator.h"

#include "Operation.h"
#include "OperationFactory.h"
#include "CalculatorException.h"
#include "sstream"
#include <memory>

void Calculator::calculate(std::istream &stream) {
    std::string line;
    while(std::getline(stream,line)) {
        std::stringstream lineStream;
        lineStream << line;

        std::string command;
        lineStream >> command; // Записать первое слово -- команду

        std::list<std::string> args;
        while(!lineStream.eof()) {  // До конца строки считывается по аргументу через " "
            std::string argument;
            lineStream >> argument;
            args.push_front(argument);
        }
        try {
            std::unique_ptr<Operation> operation = OperationFactory::getInstance().getOperation(command);
            operation->execute(args, context);
        }
        catch (CalculatorException &exception) {
            std::cout << "Error: " <<  exception.what() << std::endl;
        }

    }
}