#pragma once
#include <string>
#include "comp_pass.hpp"

class CompilerPass;

struct Expression {
    virtual void process(CompilerPass&) {};
};

struct Variable : Expression
{
    std::string name;

    Variable(const char *n);
    void process(CompilerPass&) override;
};

struct Integer : Expression
{
    int n;

    Integer (int number);
    void process(CompilerPass&) override;
};

struct PlusOpr : Expression
{
    Expression &left, &right;

    PlusOpr (Expression &left, Expression &right);
    void process(CompilerPass&) override;
};

struct Statement {
    virtual void process(CompilerPass&) {};
};

struct Assignment : Statement
{
    std::string name;
    Expression &expr;

    Assignment(const char *n, Expression &e);
    void process(CompilerPass&) override;
};

struct Return : Statement
{
    Expression &expr;

    Return (Expression &expr);
    void process(CompilerPass&);
};
