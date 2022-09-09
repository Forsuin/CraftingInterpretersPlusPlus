#pragma once


#include <string_view>
#include <vector>
#include <span>


#include "Token.hpp"

class Scanner {
private:
    const std::string_view source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 0;

public:
    Scanner(std::string_view source) : source(source) {}

    std::span<Token> scanTokens();


private:
    bool isAtEnd();
    void scanToken();
    void string();
    bool match(char expected);
    char peek();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<double, std::string_view, std::monostate> literal);

};
