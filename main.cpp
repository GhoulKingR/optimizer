#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include "comp_pass.hpp"
#include "types.hpp"

using CompilerPass = std::variant<DisplayEngine *, CopyPropagation *>;
using Expression = std::variant<
    std::shared_ptr<Variable>, std::shared_ptr<Integer>, std::shared_ptr<PlusOpr>
>;

void processStatement(Statement &stmt, CompilerPass pass) {
    if (std::holds_alternative<Return>(stmt)) {
        std::get<Return>(stmt).process(pass);
    } else {
        std::get<Assignment>(stmt).process(pass);
    }
}

int main()
{
    // create setup in object for block, equal statements, and return
    std::vector<Statement> block;

    block.push_back(Assignment("globalVariable", std::make_shared<Integer>(10)));   // let globalVariable = 15;
    block.push_back(Assignment("a", std::make_shared<Variable>("globalVariable"))); // let a = globalVariable;
    block.push_back(Assignment("b", std::make_shared<PlusOpr>(
        std::make_shared<Variable>("a"), std::make_shared<Integer>(15))));          // let b = a + 15;
    block.push_back(Assignment("ans", std::make_shared<Variable>("b")));            // let ans = b;
    block.push_back(Return(std::make_shared<Variable>("ans")));                     // return ans

    std::cout << "Before: \n";
    DisplayEngine disp;
    for (Statement &stmt : block) {
        processStatement(stmt, &disp);
    }

    // copy propagation pass
    CopyPropagation propagation;
    for (auto &stmt : block) {
        processStatement(stmt, &propagation);
    }

    std::cout << "\nAfter: \n";
    for (auto &stmt : block) {
        processStatement(stmt, &disp);
    }
    return 0;
}
