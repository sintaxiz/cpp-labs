#include "Push.h"

#include "../OperationMaker.h"
#include "../CalculatorException.h"

REGISTER_OPERATION(Push, PUSH);

void Push::execute(const std::list<std::string> &args, Context &context) {
    if (args.empty()) {
        throw NotEnoughArgsException();
    }
    if (context.hasVariable(args.back())) {
        context.pushValue(context.getVariable(args.back()));
    } else {
        context.pushValue(std::stod(args.back()));
    }
}
