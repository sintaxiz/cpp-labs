//
// Created by lumia on 10/31/2020.
//
#pragma once

#include <stack>
#include <map>
#include <list>
#include <iostream>

#include "Context.h"

class Calculator {
private:
    Context context;
public:
    Calculator() = default;

    ~Calculator() = default;

    void calculate(std::istream &stream);
};