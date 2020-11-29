#pragma once

#include "../../Operation.h"

class Division : public Operation {
public:
    void execute(const std::list<std::string> &args, Context &context) override;
};



