#pragma once
#include <string>
#include <vector>
#include <memory>
#include <variant>

struct Expr;
struct Stmt;

using ExprPtr = std::shared_ptr<Expr>;
using StmtPtr = std::shared_ptr<Stmt>;

struct Expr {
    struct Number   { double value; };
    struct String   { std::string value; };
    struct Boolean  { bool value; };
    struct Variable { std::string name; };
    struct Binary   {
        std::string op;
        ExprPtr left;
        ExprPtr right;
    };

    std::variant<
        Number,
        String,
        Boolean,
        Variable,
        Binary
    > value;
};

struct Stmt {
    struct Let {
        std::string name;
        ExprPtr value;
    };
    struct Print {
        ExprPtr value;
    };

    std::variant<
        Let,
        Print
    > value;
};
