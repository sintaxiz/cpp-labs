#pragma once

#include <string>
#include <stack>
#include <map>

// Специальный объект -- контекст исполнения
class Context {
private:
    std::stack<double> stack;
    std::map<std::string, double> variables;
public:
    double popValue();

    void pushValue(double value);

    size_t stackSize();

    void addVariable(const std::string&name, double value);

    bool hasVariable(const std::string &var);

    double getVariable(const std::string &var);

};
