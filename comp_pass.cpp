#include "comp_pass.hpp"
#include <iostream>
#include <variant>

void CopyPropagation::processAssignment(Assignment *assignment) {
    if (std::holds_alternative<std::shared_ptr<Variable>>(assignment->expr)) {
        std::shared_ptr<Variable> &var = std::get<std::shared_ptr<Variable>>(assignment->expr);
        var->process(this);
        passed[assignment->name] = var->name;
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(assignment->expr)) {
        std::get<std::shared_ptr<Integer>>(assignment->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(assignment->expr)) {
        std::get<std::shared_ptr<PlusOpr>>(assignment->expr)->process(this);
    }
}

void CopyPropagation::processVariable(Variable *var) {
    if(passed.find(var->name) != passed.end()) {
        var->name = passed[var->name];
    }
}

void CopyPropagation::processPlusOpr(PlusOpr *opr) {
    if (std::holds_alternative<std::shared_ptr<Variable>>(opr->left)) {
        std::get<std::shared_ptr<Variable>>(opr->left)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(opr->left)) {
        std::get<std::shared_ptr<Integer>>(opr->left)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(opr->left)) {
        std::get<std::shared_ptr<PlusOpr>>(opr->left)->process(this);
    }

    if (std::holds_alternative<std::shared_ptr<Variable>>(opr->right)) {
        std::get<std::shared_ptr<Variable>>(opr->right)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(opr->right)) {
        std::get<std::shared_ptr<Integer>>(opr->right)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(opr->right)) {
        std::get<std::shared_ptr<PlusOpr>>(opr->right)->process(this);
    }
}

void CopyPropagation::processInteger(Integer *) {}

void CopyPropagation::processReturn(Return *ret) {
    if (std::holds_alternative<std::shared_ptr<Variable>>(ret->expr)) {
        std::get<std::shared_ptr<Variable>>(ret->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(ret->expr)) {
        std::get<std::shared_ptr<Integer>>(ret->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(ret->expr)) {
        std::get<std::shared_ptr<PlusOpr>>(ret->expr)->process(this);
    }
}

void DisplayEngine::processReturn(Return *ret) {
    std::cout << "return ";

    if (std::holds_alternative<std::shared_ptr<Variable>>(ret->expr)) {
        std::get<std::shared_ptr<Variable>>(ret->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(ret->expr)) {
        std::get<std::shared_ptr<Integer>>(ret->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(ret->expr)) {
        std::get<std::shared_ptr<PlusOpr>>(ret->expr)->process(this);
    }

    std::cout << ";\n";
}

void DisplayEngine::processPlusOpr(PlusOpr *opr) {
    if (std::holds_alternative<std::shared_ptr<Variable>>(opr->left)) {
        std::get<std::shared_ptr<Variable>>(opr->left)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(opr->left)) {
        std::get<std::shared_ptr<Integer>>(opr->left)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(opr->left)) {
        std::get<std::shared_ptr<PlusOpr>>(opr->left)->process(this);
    }

    std::cout << " + ";

    if (std::holds_alternative<std::shared_ptr<Variable>>(opr->right)) {
        std::get<std::shared_ptr<Variable>>(opr->right)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(opr->right)) {
        std::get<std::shared_ptr<Integer>>(opr->right)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(opr->right)) {
        std::get<std::shared_ptr<PlusOpr>>(opr->right)->process(this);
    }
}

void DisplayEngine::processInteger(Integer *num) {
    std::cout << num->n;
}

void DisplayEngine::processVariable(Variable *var) {
    std::cout << var->name;
}

void DisplayEngine::processAssignment(Assignment *assignment) {
    std::cout << "let " << assignment->name << " = ";
    if (std::holds_alternative<std::shared_ptr<Variable>>(assignment->expr)) {
        std::get<std::shared_ptr<Variable>>(assignment->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<Integer>>(assignment->expr)) {
        std::get<std::shared_ptr<Integer>>(assignment->expr)->process(this);
    } else if (std::holds_alternative<std::shared_ptr<PlusOpr>>(assignment->expr)) {
        std::get<std::shared_ptr<PlusOpr>>(assignment->expr)->process(this);
    }
    std::cout << ";\n";
}
