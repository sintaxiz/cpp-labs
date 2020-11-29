#pragma once

#include "../../Operation.h"

class Root : public Operation {
public:
    void execute(const std::list<std::string> &args, Context &context) override;
};



