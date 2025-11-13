#include "evaluator.hpp"
#include "ast.hpp"      // ★ 반드시 필요

#include <memory>
#include <iostream>

void Evaluator::run(const std::vector<StmtPtr>& stmts) {
    for (auto& s : stmts) {

        // Statement 가 ExprStmt인지 확인
        auto es = std::dynamic_pointer_cast<ExprStmt>(s);
        if (!es) continue;

        // ExprStmt 안이 PrintExpr인지 확인
        auto p = std::dynamic_pointer_cast<PrintExpr>(es->expr);
        if (p) {
            // PrintExpr 안이 NumberExpr인지 확인
            auto num = std::dynamic_pointer_cast<NumberExpr>(p->value);
            if (num) {
                std::cout << "[Swift Runtime] print → " << num->value << "\n";
            }
        }
    }
}
