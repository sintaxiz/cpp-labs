#pragma once

#include "InterfaceOperationMaker.h"
#include "OperationFactory.h"
#include <memory>

#define REGISTER_OPERATION(T, NAME) static OperationMaker<T> maker(#NAME);


template<typename T>
class OperationMaker : public InterfaceOperationMaker
{
public:
    OperationMaker(const std::string& name) {
        OperationFactory::getInstance().registerMaker(name, this);
    }

    virtual std::unique_ptr<Operation> create() const override {
        std::unique_ptr<Operation> ptr(new T());
        return ptr;
    }
};