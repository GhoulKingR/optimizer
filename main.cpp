#include <iostream>
#include "comp_pass.hpp"
#include "types.hpp"

void processStatement(Statement *stmt, CompilerPass *pass) {
    stmt->process(pass);
}

int main()
{
    // create setup in object for block, equal statements, and return
    std::array<Statement*, 5> block;

    Integer n(10);
    Assignment s1("globalVariable", &n);
    block[0] = &s1;                       // let globalVariable = 15;

    Variable global("globalVariable");
    Assignment s2("a", &global);
    block[1] = &s2;                       // let a = globalVariable;

    Variable a("a");
    Integer  i15(15);
    PlusOpr  opr(&a, &i15);
    Assignment s3("b", &opr);
    block[2] = &s3;                       // let b = a + 15;

    Variable b("b");
    Assignment s4("ans", &b);
    block[3] = &s4;                       // let ans = b;

    Variable ans("ans");
    Return s5(&ans);
    block[4] = &s5;                       // return ans

    std::cout << "Before: \n";
    DisplayEngine disp;
    for (Statement *stmt : block) {
        processStatement(stmt, &disp);
    }

    // copy propagation pass
    CopyPropagation propagation;
    for (Statement *stmt : block) {
        processStatement(stmt, &propagation);
    }

    std::cout << "\nAfter: \n";
    for (Statement *stmt : block) {
        processStatement(stmt, &disp);
    }
    return 0;
}
