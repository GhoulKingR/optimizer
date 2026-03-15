#include "types.hpp"

Variable::Variable(std::string n): name(n) {}

void Variable::process(CompilerPass &pass) {
    pass.processVariable(*this);
}

Integer::Integer (int number): n(number) {}

void Integer::process(CompilerPass &pass) {
    pass.processInteger(*this);
}

PlusOpr::PlusOpr (Expression &left, Expression &right)
    : left(left), right(right)
{}

void PlusOpr::process(CompilerPass &pass) {
    pass.processPlusOpr(*this);
}

Assignment::Assignment(std::string n, Expression &e)
    : name(n), expr(e)
{}

void Assignment::process(CompilerPass &pass) {
    pass.processAssignment(*this);
}

Return::Return (Expression &expr)
    : expr(expr)
{}

void Return::process(CompilerPass &pass) {
    pass.processReturn(*this);
}

