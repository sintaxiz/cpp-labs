#include "Print.h"

#include <iostream>

#include "../OperationMaker.h"
#include "../CalculatorException.h"

REGISTER_OPERATION(Print, PRINT);

void Print::execute(const std::list<std::string> &args, Context &context) {
    if (context.stackSize() <= 0) {
        throw NotEnoughArgsException();
    }
    std::cout << context.popValue() << std::endl;
}
