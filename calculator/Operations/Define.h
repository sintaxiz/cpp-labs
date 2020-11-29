#pragma once

#include "../Operation.h"

class Define : public Operation {
public:
    void execute(const std::list<std::string> &args, Context &context) override;
};



