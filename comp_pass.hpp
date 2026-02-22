#pragma once
#include "types.hpp"
#include <unordered_map>

struct Assignment;
struct Return;
struct Variable;
struct Integer;
struct PlusOpr;

using Expression = std::variant<
    std::shared_ptr<Variable>, std::shared_ptr<Integer>, std::shared_ptr<PlusOpr>
>;

class CopyPropagation
{
    std::unordered_map<std::string, std::string> passed;
    void processExpression(Expression expr);
public:
    void processAssignment(Assignment *assignment);
    void processVariable(Variable *var);
    void processInteger(Integer *);
    void processPlusOpr(PlusOpr *opr);
    void processReturn(Return *ret);
};

class DisplayEngine
{
    void processExpression(Expression expr);
public:
    void processReturn(Return *ret);
    void processPlusOpr(PlusOpr *opr);
    void processInteger(Integer *num);
    void processVariable(Variable *var);
    void processAssignment(Assignment *ass);
};

using CompilerPass = std::variant<DisplayEngine *, CopyPropagation *>;
