#include "ast.hpp"
#include "parser.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

// 숫자 체크
bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    return std::all_of(s.begin(), s.end(), ::isdigit);
}

// 안전 stoi
int safeInt(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return 0;
    }
}

std::vector<StmtPtr> Parser::parseProgram() {
    std::vector<StmtPtr> result;

    std::istringstream ss(code);
    std::string line;

    while (std::getline(ss, line)) {

        // 앞뒤 공백 제거
        line.erase(std::remove_if(line.begin(), line.end(),
                                  [](unsigned char c){ return c==' ' || c=='\r' || c=='\t'; }),
                    line.end());

        // print(...) 문 확인
        if (line.rfind("print(", 0) == 0 && line.back() == ')') {

            // 내부 추출
            std::string inside = line.substr(6, line.size() - 7);

            // 앞뒤 공백 제거
            inside.erase(std::remove_if(inside.begin(), inside.end(),
                                        [](unsigned char c){ return c==' ' || c=='\r' || c=='\t'; }),
                         inside.end());

            // 내부가 숫자인 경우
            int v = isNumber(inside) ? safeInt(inside) : 0;

            // AST 생성
            result.push_back(std::make_shared<ExprStmt>(
                std::make_shared<PrintExpr>(
                    std::make_shared<NumberExpr>(v)
                )
            ));
        }
    }

    return result;
}
