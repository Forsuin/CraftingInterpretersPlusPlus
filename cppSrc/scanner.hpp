#pragma once


#include <string_view>
#include <vector>
#include <span>
#include <unordered_map>


#include "Token.hpp"

class Scanner {
private:
    const std::string_view source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 0;

    static std::unordered_map<std::string_view, TokenType> keywords;


public:
    Scanner(std::string_view source) : source(source) {}

    std::span<Token> scanTokens();

private:
    bool isAtEnd();
    void scanToken();
    void identifier();
    void number();
    void string();
    bool match(char expected);
    char peek();
    char peekNext();
    bool isAlpha(char c);
    bool isDigit(char c);
    bool isAlphaNumeric(char c);
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<double, std::string_view, std::monostate> literal);

};
