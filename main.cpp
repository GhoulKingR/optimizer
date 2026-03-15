#include <array>
#include <functional>
#include <iostream>
#include "comp_pass.hpp"
#include "types.hpp"

int main()
{
    Integer n(10);
    Assignment s1("globalVariable", n);

    Variable global("globalVariable");
    Assignment s2("a", global);

    Variable a("a");
    Integer  i15(15);
    PlusOpr  opr(a, i15);
    Assignment s3("b", opr);

    Variable b("b");
    Assignment s4("ans", b);

    Variable ans("ans");
    Return s5(ans);

    // create setup in object for block, equal statements, and return
    std::array<std::reference_wrapper<Statement>, 5> block = {
        s1, s2, s3, s4, s5
    };

    std::cout << "Before: \n";
    DisplayEngine disp;
    for (Statement &stmt : block) {
        disp.processStatement(stmt);
    }

    // copy propagation pass
    CopyPropagation propagation;
    for (Statement &stmt : block) {
        propagation.processStatement(stmt);
    }

    std::cout << "\nAfter: \n";
    for (Statement &stmt : block) {
        disp.processStatement(stmt);
    }
    return 0;
}
