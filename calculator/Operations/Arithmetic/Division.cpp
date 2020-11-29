#include "Division.h"

#include "../../OperationMaker.h"
#include "../../CalculatorException.h"

REGISTER_OPERATION(Division, /);

void Division::execute(const std::list<std::string> &args, Context &context) {
    if (context.stackSize() < 2) {
        throw NotEnoughArgsException();
    }
    double numerator = context.popValue();
    double denominator = context.popValue();
    if (denominator == 0) {
        throw DivisionByZeroException();
    }
    context.pushValue(numerator / denominator);
}
