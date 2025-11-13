#include "parser.hpp"
#include <sstream>

Parser::Parser(const std::string &src) : pos(0) {
    tokenize(src);
}

void Parser::tokenize(const std::string &src) {
    int i = 0;
    while (i < src.size()) {
        char c = src[i];

        if (isspace(c)) { i++; continue; }

        if (isdigit(c)) {
            int start = i;
            while (i < src.size() && (isdigit(src[i]) || src[i] == '.')) i++;
            tokens.push_back({NUMBER, src.substr(start, i - start)});
            continue;
        }

        if (isalpha(c)) {
            int start = i;
            while (i < src.size() && (isalnum(src[i]) || src[i] == '_')) i++;
            std::string word = src.substr(start, i - start);

            if (word == "let")    tokens.push_back({LET, word});
            else if (word == "print") tokens.push_back({PRINT, word});
            else if (word == "true")  tokens.push_back({TRUE, word});
            else if (word == "false") tokens.push_back({FALSE, word});
            else tokens.push_back({IDENT, word});
            continue;
        }

        if (c == '"') {
            i++;
            int start = i;
            while (i < src.size() && src[i] != '"') i++;
            std::string str = src.substr(start, i - start);
            i++;
            tokens.push_back({STRING, str});
            continue;
        }

        switch (c) {
            case '=': tokens.push_back({EQUAL, "="}); break;
            case '(': tokens.push_back({LPAREN, "("}); break;
            case ')': tokens.push_back({RPAREN, ")"}); break;
            case ';': tokens.push_back({SEMI, ";"}); break;
            default:
                tokens.push_back({OP, std::string(1, c)});
        }
        i++;
    }

    tokens.push_back({END, ""});
}

Parser::Token Parser::peek() const { return tokens[pos]; }
Parser::Token Parser::get() { return tokens[pos++]; }

bool Parser::match(TokenType t) {
    if (peek().type == t) { pos++; return true; }
    return false;
}

std::vector<StmtPtr> Parser::parseProgram() {
    std::vector<StmtPtr> stmts;
    while (peek().type != END) {
        stmts.push_back(parseStatement());
        match(SEMI); // optional
    }
    return stmts;
}

StmtPtr Parser::parseStatement() {
    if (match(LET)) return parseLet();
    if (match(PRINT)) return parsePrint();
    throw std::runtime_error("Unknown statement");
}

StmtPtr Parser::parseLet() {
    Token nameTok = get();
    if (nameTok.type != IDENT) throw std::runtime_error("Expected identifier");

    if (!match(EQUAL)) throw std::runtime_error("Expected '='");

    ExprPtr value = parseExpr();

    auto st = std::make_shared<Stmt>();
    st->value = Stmt::Let{nameTok.text, value};
    return st;
}

StmtPtr Parser::parsePrint() {
    ExprPtr value = parseExpr();
    auto st = std::make_shared<Stmt>();
    st->value = Stmt::Print{value};
    return st;
}

ExprPtr Parser::parseExpr() {
    ExprPtr left = parseTerm();

    while (peek().type == OP &&
          (peek().text == "+" || peek().text == "-")) {
        std::string op = get().text;
        ExprPtr right = parseTerm();
        auto e = std::make_shared<Expr>();
        e->value = Expr::Binary{op, left, right};
        left = e;
    }
    return left;
}

ExprPtr Parser::parseTerm() {
    ExprPtr left = parseFactor();

    while (peek().type == OP &&
          (peek().text == "*" || peek().text == "/")) {
        std::string op = get().text;
        ExprPtr right = parseFactor();
        auto e = std::make_shared<Expr>();
        e->value = Expr::Binary{op, left, right};
        left = e;
    }
    return left;
}

ExprPtr Parser::parseFactor() {
    Token t = get();

    if (t.type == NUMBER) {
        auto e = std::make_shared<Expr>();
        e->value = Expr::Number{std::stod(t.text)};
        return e;
    }

    if (t.type == STRING) {
        auto e = std::make_shared<Expr>();
        e->value = Expr::String{t.text};
        return e;
    }

    if (t.type == TRUE || t.type == FALSE) {
        auto e = std::make_shared<Expr>();
        e->value = Expr::Boolean{t.type == TRUE};
        return e;
    }

    if (t.type == IDENT) {
        auto e = std::make_shared<Expr>();
        e->value = Expr::Variable{t.text};
        return e;
    }

    if (t.type == LPAREN) {
        ExprPtr e = parseExpr();
        if (!match(RPAREN)) throw std::runtime_error("Expected ')'");
        return e;
    }

    throw std::runtime_error("Unexpected token in factor");
}
