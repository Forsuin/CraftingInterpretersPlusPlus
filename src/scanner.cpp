#include "scanner.hpp"
#include "lox.hpp"

std::span<Token> Scanner::scanTokens() {
    while(!isAtEnd()){
        start = current;
        scanToken();
    }

    tokens.push_back(Token(TokenType::EOF, "", std::monostate{}, line));
    return std::span{tokens};
}

bool Scanner::isAtEnd() {
    return current >= source.length();
}

void Scanner::scanToken() {
    char c = advance();

    switch (c) {
        case '(' :
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')' :
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{' :
            addToken(TokenType::LEFT_BRACE);
            break;
        case '}' :
            addToken(TokenType::RIGHT_BRACE);
            break;
        case ',' :
            addToken(TokenType::COMMA);
            break;
        case '.' :
            addToken(TokenType::DOT);
            break;
        case '-' :
            addToken(TokenType::MINUS);
            break;
        case '+' :
            addToken(TokenType::PLUS);
            break;
        case ';' :
            addToken(TokenType::SEMICOLON);
            break;
        case '*' :
            addToken(TokenType::STAR);
            break;

    }
}
char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, std::monostate{});
}

void Scanner::addToken(TokenType type, std::variant<double, std::string_view, std::monostate> literal) {
    std::string_view text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}