#include "Root.h"

#include <cmath>

#include "../../OperationMaker.h"
#include "../../CalculatorException.h"

REGISTER_OPERATION(Root, SQRT);

void Root::execute(const std::list<std::string> &args, Context &context) {
    if (context.stackSize() < 1) {
        throw NotEnoughArgsException();
    }
    context.pushValue(sqrt(context.popValue()));
}
