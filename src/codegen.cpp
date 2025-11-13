#include "codegen.hpp"
#include <sstream>

std::string CodeGen::generate(const std::vector<StmtPtr>& prog) {
    std::stringstream out;

    out << "#include <iostream>\n";
    out << "#include <string>\n";
    out << "using namespace std;\n\n";
    out << "int main() {\n";

    for (auto &st : prog) {
        if (std::holds_alternative<Stmt::Let>(st->value)) {
            auto& v = std::get<Stmt::Let>(st->value);
            out << "    auto " << v.name << " = " << genExpr(v.value) << ";\n";
        }
        else if (std::holds_alternative<Stmt::Print>(st->value)) {
            auto& v = std::get<Stmt::Print>(st->value);
            out << "    cout << " << genExpr(v.value) << " << endl;\n";
        }
    }

    out << "    return 0;\n";
    out << "}\n\n";

    return out.str();
}

std::string CodeGen::genExpr(const ExprPtr& e) {
    if (std::holds_alternative<Expr::Number>(e->value))
        return std::to_string(std::get<Expr::Number>(e->value).value);

    if (std::holds_alternative<Expr::String>(e->value))
        return "\"" + std::get<Expr::String>(e->value).value + "\"";

    if (std::holds_alternative<Expr::Boolean>(e->value))
        return std::get<Expr::Boolean>(e->value).value ? "true" : "false";

    if (std::holds_alternative<Expr::Variable>(e->value))
        return std::get<Expr::Variable>(e->value).name;

    if (std::holds_alternative<Expr::Binary>(e->value)) {
        auto& b = std::get<Expr::Binary>(e->value);
        return "(" + genExpr(b.left) + " " + b.op + " " + genExpr(b.right) + ")";
    }

    return "";
}
