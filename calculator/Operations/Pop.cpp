#include "Pop.h"

#include "../OperationMaker.h"
#include "../CalculatorException.h"

REGISTER_OPERATION(Pop, POP);

void Pop::execute(const std::list<std::string> &args, Context &context) {
    if (context.stackSize() < 1) {
        throw NotEnoughArgsException();
    }
    context.popValue();
}
