#include "types.hpp"
#include <variant>

Variable::Variable(std::string n): name(n) {}

void Variable::process(CompilerPass pass) {
    if (std::holds_alternative<DisplayEngine *>(pass)) {
        std::get<DisplayEngine *>(pass)->processVariable(this);
    } else if (std::holds_alternative<CopyPropagation *>(pass)) {
        std::get<CopyPropagation *>(pass)->processVariable(this);
    }
}

Integer::Integer (int number): n(number) {}

void Integer::process(CompilerPass pass) {
    if (std::holds_alternative<DisplayEngine *>(pass)) {
        std::get<DisplayEngine *>(pass)->processInteger(this);
    } else if (std::holds_alternative<CopyPropagation *>(pass)) {
        std::get<CopyPropagation *>(pass)->processInteger(this);
    }
}

PlusOpr::PlusOpr (Expression left, Expression right): left(left), right(right) {}

void PlusOpr::process(CompilerPass pass) {
    if (std::holds_alternative<DisplayEngine *>(pass)) {
        std::get<DisplayEngine *>(pass)->processPlusOpr(this);
    } else if (std::holds_alternative<CopyPropagation *>(pass)) {
        std::get<CopyPropagation *>(pass)->processPlusOpr(this);
    }
}

Assignment::Assignment(std::string n, Expression e): name(n), expr(e) {}

void Assignment::process(CompilerPass pass) {
    if (std::holds_alternative<DisplayEngine *>(pass)) {
        std::get<DisplayEngine *>(pass)->processAssignment(this);
    } else if (std::holds_alternative<CopyPropagation *>(pass)) {
        std::get<CopyPropagation *>(pass)->processAssignment(this);
    }
}

Return::Return (Expression expr): expr(expr) {}

void Return::process(CompilerPass pass) {
    if (std::holds_alternative<DisplayEngine *>(pass)) {
        std::get<DisplayEngine *>(pass)->processReturn(this);
    } else if (std::holds_alternative<CopyPropagation *>(pass)) {
        std::get<CopyPropagation *>(pass)->processReturn(this);
    }
}

