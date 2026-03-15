#pragma once
#include "types.hpp"
#include <unordered_map>

struct Assignment;
struct Return;
struct Variable;
struct Integer;
struct PlusOpr;
struct Expression;
struct Statement;

class CompilerPass {
    virtual void processExpression(Expression &expr) {}
public:
    virtual void processAssignment(Assignment &assignment) {}
    virtual void processVariable(Variable &var) {}
    virtual void processInteger(Integer &) {}
    virtual void processPlusOpr(PlusOpr &opr) {}
    virtual void processReturn(Return &ret) {}
    virtual void processStatement(Statement &stmt) {}
};

class CopyPropagation : public CompilerPass
{
    std::unordered_map<std::string, std::string> passed;
    void processExpression(Expression &expr) override;
public:
    void processAssignment(Assignment &assignment) override;
    void processVariable(Variable &var) override;
    void processInteger(Integer &) override;
    void processPlusOpr(PlusOpr &opr) override;
    void processReturn(Return &ret) override;
    void processStatement(Statement &stmt) override;
};

class DisplayEngine : public CompilerPass
{
    void processExpression(Expression &expr) override;
public:
    void processReturn(Return &ret) override;
    void processPlusOpr(PlusOpr &opr) override;
    void processInteger(Integer &num) override;
    void processVariable(Variable &var) override;
    void processAssignment(Assignment &ass) override;
    void processStatement(Statement &stmt) override;
};
