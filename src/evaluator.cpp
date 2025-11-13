#include "evaluator.hpp"

void Evaluator::run(const std::vector<StmtPtr>& stmts) {
    for (auto& s : stmts) {
        auto es = std::dynamic_pointer_cast<ExprStmt>(s);
        if (!es) continue;

        if (auto p = std::dynamic_pointer_cast<PrintExpr>(es->expr)) {
            auto num = std::dynamic_pointer_cast<NumberExpr>(p->value);
            if (num) {
                std::cout << "[Swift Runtime] print → " << num->value << "\n";
            }
        }
    }
}
