#include "Multiplication.h"

#include "../../OperationMaker.h"
#include "../../CalculatorException.h"

REGISTER_OPERATION(Multiplication, *);

void Multiplication::execute(const std::list<std::string> &args, Context &context) {
    if (context.stackSize() < 2) {
        throw NotEnoughArgsException();
    }
    context.pushValue(context.popValue() * context.popValue());
}
