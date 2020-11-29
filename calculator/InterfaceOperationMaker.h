#pragma once

#include "Operation.h"
#include <memory>

class InterfaceOperationMaker {
public:
    virtual std::unique_ptr<Operation> create() const = 0;

    virtual ~InterfaceOperationMaker() = default;
};

