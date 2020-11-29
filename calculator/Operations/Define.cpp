#include "Define.h"

#include "../OperationMaker.h"
#include "../CalculatorException.h"

REGISTER_OPERATION(Define, DEFINE);

void Define::execute(const std::list<std::string> &args, Context &context) {
    if (args.size() < 2) {
        throw NotEnoughArgsException();
    }
    context.addVariable(args.back(), std::stod(args.front()));
}
