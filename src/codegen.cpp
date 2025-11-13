#include "codegen.hpp"
#include <stdexcept>

void Evaluator::run(const std::vector<StmtPtr> &program) {
    for (auto &st : program) {
        if (std::holds_alternative<Stmt::Let>(st->value)) {
            auto &v = std::get<Stmt::Let>(st->value);
            env[v.name] = evalExpr(v.value);
        }
        else if (std::holds_alternative<Stmt::Print>(st->value)) {
            auto &v = std::get<Stmt::Print>(st->value);
            auto r = evalExpr(v.value);

            if (std::holds_alternative<double>(r))
                std::cout << std::get<double>(r) << "\n";
            else if (std::holds_alternative<std::string>(r))
                std::cout << std::get<std::string>(r) << "\n";
            else if (std::holds_alternative<bool>(r))
                std::cout << (std::get<bool>(r) ? "true" : "false") << "\n";
        }
    }
}

auto Evaluator::evalExpr(const ExprPtr &e)
-> std::variant<double, std::string, bool>
{
    if (std::holds_alternative<Expr::Number>(e->value))
        return std::get<Expr::Number>(e->value).value;

    if (std::holds_alternative<Expr::String>(e->value))
        return std::get<Expr::String>(e->value).value;

    if (std::holds_alternative<Expr::Boolean>(e->value))
        return std::get<Expr::Boolean>(e->value).value;

    if (std::holds_alternative<Expr::Variable>(e->value)) {
        auto &name = std::get<Expr::Variable>(e->value).name;
        if (!env.count(name)) throw std::runtime_error("Undefined variable: " + name);
        return env[name];
    }

    if (std::holds_alternative<Expr::Binary>(e->value)) {
        auto &b = std::get<Expr::Binary>(e->value);
        auto lv = evalExpr(b.left);
        auto rv = evalExpr(b.right);

        double l = std::get<double>(lv);
        double r = std::get<double>(rv);

        if (b.op == "+") return l + r;
        if (b.op == "-") return l - r;
        if (b.op == "*") return l * r;
        if (b.op == "/") return l / r;

        throw std::runtime_error("Unknown operator: " + b.op);
    }

    throw std::runtime_error("Invalid expression");
}
