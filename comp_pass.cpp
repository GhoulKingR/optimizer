#include "comp_pass.hpp"
#include <iostream>
#include <variant>

void CopyPropagation::processExpression(Expression expr) {
    if (std::holds_alternative<std::shared_ptr<Variable>>(expr)) {
        std::get<std::shared_ptr<Variable>>(expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(expr)) {
        std::get<std::shared_ptr<Integer>>(expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(expr)) {
        std::get<std::shared_ptr<PlusOpr>>(expr)->process(this);
    }
}

void CopyPropagation::processAssignment(Assignment *assignment) {
    processExpression(assignment->expr);

    if (std::holds_alternative<std::shared_ptr<Variable>>(assignment->expr)) {
        std::shared_ptr<Variable> &var = std::get<std::shared_ptr<Variable>>(assignment->expr);
        passed[assignment->name] = var->name;
    }
}

void CopyPropagation::processVariable(Variable *var) {
    if(passed.find(var->name) != passed.end()) {
        var->name = passed[var->name];
    }
}

void CopyPropagation::processPlusOpr(PlusOpr *opr) {
    processExpression(opr->left);
    processExpression(opr->right);
}

void CopyPropagation::processInteger(Integer *) {}

void CopyPropagation::processReturn(Return *ret) {
    processExpression(ret->expr);
}

void DisplayEngine::processExpression(Expression expr) {
    if (std::holds_alternative<std::shared_ptr<Variable>>(expr)) {
        std::get<std::shared_ptr<Variable>>(expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(expr)) {
        std::get<std::shared_ptr<Integer>>(expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(expr)) {
        std::get<std::shared_ptr<PlusOpr>>(expr)->process(this);
    }

}

void DisplayEngine::processReturn(Return *ret) {
    std::cout << "return ";
    processExpression(ret->expr);
    std::cout << ";\n";
}

void DisplayEngine::processPlusOpr(PlusOpr *opr) {
    processExpression(opr->left);
    std::cout << " + ";
    processExpression(opr->right);
}

void DisplayEngine::processInteger(Integer *num) {
    std::cout << num->n;
}

void DisplayEngine::processVariable(Variable *var) {
    std::cout << var->name;
}

void DisplayEngine::processAssignment(Assignment *assignment) {
    std::cout << "let " << assignment->name << " = ";
    processExpression(assignment->expr);
    std::cout << ";\n";
}
