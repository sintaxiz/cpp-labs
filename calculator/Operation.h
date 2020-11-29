#pragma once

#include "Context.h"

#include <list>
#include <string>

class Operation {
public:
    virtual void execute(const std::list<std::string> &args, Context &context) = 0;

    virtual ~Operation() = default;
};

