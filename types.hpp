#pragma once
#include <memory>
#include <string>
#include <variant>
#include "comp_pass.hpp"

class DisplayEngine;
class CopyPropagation;
class Variable;
class Integer;
class PlusOpr;

using CompilerPass = std::variant<DisplayEngine *, CopyPropagation *>;
using Expression = std::variant<
    std::shared_ptr<Variable>, std::shared_ptr<Integer>, std::shared_ptr<PlusOpr>
>;

struct Variable
{
    std::string name;

    Variable(std::string n);
    void process(CompilerPass);
};

struct Integer
{
    int n;

    Integer (int number);
    void process(CompilerPass);
};

struct PlusOpr
{
    Expression left, right;

    PlusOpr (Expression left, Expression right);
    void process(CompilerPass);
};

struct Assignment
{
    std::string name;
    Expression expr;

    Assignment(std::string n, Expression e);
    void process(CompilerPass);
};

struct Return
{
    Expression expr;

    Return (Expression expr);
    void process(CompilerPass);
};

using Statement = std::variant<Assignment, Return>;
