#pragma once

#include "../../Operation.h"

class Plus : public Operation {
public:
    void execute(const std::list<std::string> &args, Context &context) override;
};

