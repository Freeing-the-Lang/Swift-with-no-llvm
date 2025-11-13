#pragma once
#include <memory>
#include <vector>
#include <string>

// ===== Base Types =====
struct Expr {
    virtual ~Expr() = default;
};

struct Stmt {
    virtual ~Stmt() = default;
};

// ===== Expr Types =====

struct NumberExpr : public Expr {
    double value;
    NumberExpr(double v) : value(v) {}
};

struct PrintExpr : public Expr {
    std::shared_ptr<Expr> value;
    PrintExpr(std::shared_ptr<Expr> v) : value(v) {}
};

// ===== Stmt Types =====

struct ExprStmt : public Stmt {
    std::shared_ptr<Expr> expr;
    ExprStmt(std::shared_ptr<Expr> e) : expr(e) {}
};
