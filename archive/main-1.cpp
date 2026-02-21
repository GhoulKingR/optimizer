#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include "comp_pass.hpp"
#include "types.hpp"

int main()
{
    // create setup in object for block, equal statements, and return
    std::vector<Statement> block;

    block.push_back(Assignment("a", std::make_shared<PlusOpr>(
        std::make_shared<Integer>(1), std::make_shared<Integer>(2))));          // let a = 1 + 2;
    block.push_back(Assignment("b", std::make_shared<Variable>("a")));          // let b = a;
    block.push_back(Assignment("ans", std::make_shared<PlusOpr>(
        std::make_shared<Variable>("b"), std::make_shared<Integer>(6))));       // let ans = b + 6;
    block.push_back(Return(std::make_shared<Variable>("ans")));                 // return ans

    std::cout << "Before: \n";
    DisplayEngine disp;
    for (Statement &stmt : block) {
        if (std::holds_alternative<Return>(stmt)) {
            std::get<Return>(stmt).process(&disp);
        } else {
            std::get<Assignment>(stmt).process(&disp);
        }
    }

    // copy propagation pass
    CopyPropagation propagation;
    for (auto &stmt : block) {
        if (std::holds_alternative<Return>(stmt)) {
            std::get<Return>(stmt).process(&propagation);
        } else {
            std::get<Assignment>(stmt).process(&propagation);
        }
    }

    std::cout << "\nAfter: \n";
    for (auto &stmt : block) {
        if (std::holds_alternative<Return>(stmt)) {
            std::get<Return>(stmt).process(&disp);
        } else {
            std::get<Assignment>(stmt).process(&disp);
        }
    }
    return 0;
}
