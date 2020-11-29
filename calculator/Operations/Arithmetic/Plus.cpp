#include "Plus.h"

#include "../../OperationMaker.h"
#include "../../CalculatorException.h"

REGISTER_OPERATION(Plus, +);

void Plus::execute(const std::list<std::string> &args, Context &context) {
    {
        if (context.stackSize() < 2) {
            throw NotEnoughArgsException();
        }
        context.pushValue(context.popValue() + context.popValue());
    }
}
