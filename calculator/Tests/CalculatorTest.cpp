
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include "../Calculator.h"

class CalculatorTest : public testing ::Test {
protected:
    void SetUp() override {
        //freopen(R"(C:\Users\lumia\Documents\output.txt)","w",stdout);
        //OperationFactory &factory = OperationFactory::getInstance();
    }
    void TearDown() override {

    }
};

TEST_F(CalculatorTest, baseTest) {
    Calculator calc;
    std::stringstream f("PUSH 3\nPUSH 10\n+\nPRINT");
    calc.calculate(f);
}

TEST_F(CalculatorTest, defineTest) {
    Calculator calc;
    std::stringstream input("DEFINE a 10\nDEFINE b 23\nPUSH a\nPUSH b\n*\nPRINT");
    calc.calculate(input);
}

TEST_F(CalculatorTest, divisionTest) {
    Calculator calc;
    std::stringstream input("PUSH 0\nPUSH 10\n/\nPRINT");
    calc.calculate(input);
    std::stringstream input2("PUSH 100\nPUSH 10\n/\nPRINT");
    calc.calculate(input2);
    std::stringstream input3("PUSH 10\nPUSH 100\n/\nPRINT");
    calc.calculate(input3);
}
