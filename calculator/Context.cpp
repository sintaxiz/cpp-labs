#include "Context.h"
#include "CalculatorException.h"

double Context::popValue() {
    double value = stack.top();
    stack.pop();
    return value;
}

void Context::pushValue(double value) {
    stack.push(value);
}

size_t Context::stackSize() {
    return stack.size();
}

void Context::addVariable(const std::string&name, double value) {
    variables[name] = value;
}

bool Context::hasVariable(const std::string &var) {
    return variables.find(var) != variables.end();
}

double Context::getVariable(const std::string &var) {
    if (hasVariable(var)){
        return variables.at(var);
    } else {
        throw WrongVarException();
    }
}
