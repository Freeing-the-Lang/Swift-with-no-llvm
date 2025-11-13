#pragma once
#include "ast.hpp"
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

class Parser {
public:
    Parser(const std::string &src);

    std::vector<StmtPtr> parseProgram();

private:
    // token type
    enum TokenType {
        IDENT, NUMBER, STRING, OP,
        LET, PRINT, TRUE, FALSE,
        LPAREN, RPAREN, EQUAL, SEMI,
        END
    };

    struct Token {
        TokenType type;
        std::string text;
    };

    std::vector<Token> tokens;
    int pos;

    void tokenize(const std::string &src);

    Token peek() const;
    Token get();
    bool match(TokenType t);

    StmtPtr parseStatement();
    StmtPtr parseLet();
    StmtPtr parsePrint();

    ExprPtr parseExpr();
    ExprPtr parseTerm();
    ExprPtr parseFactor();
};
