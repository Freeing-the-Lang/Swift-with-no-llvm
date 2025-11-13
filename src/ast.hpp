#pragma once
#include <memory>
#include <vector>
#include <string>

// 기본 인터페이스
struct Expr {
    virtual ~Expr() = default;
};

struct Stmt {
    virtual ~Stmt() = default;
};

// 스마트 포인터 alias
using ExprPtr = std::shared_ptr<Expr>;
using StmtPtr = std::shared_ptr<Stmt>;

// ===== Expression Types =====

struct NumberExpr : public Expr {
    double value;
    NumberExpr(double v) : value(v) {}
};

struct PrintExpr : public Expr {
    ExprPtr value;
    PrintExpr(ExprPtr v) : value(v) {}
};

// ===== Statement Types =====

struct ExprStmt : public Stmt {
    ExprPtr expr;
    ExprStmt(ExprPtr e) : expr(e) {}
};
