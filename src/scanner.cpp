#include <string>

#include "scanner.hpp"
#include "loxError.hpp"


std::unordered_map<std::string_view, TokenType> Scanner::keywords = {
        { "and",    TokenType::AND },
        { "class",  TokenType::CLASS },
        { "else",   TokenType::ELSE },
        { "false",  TokenType::FALSE },
        { "for",    TokenType::FOR },
        { "fun",    TokenType::FUN },
        { "if",     TokenType::IF },
        { "nil",    TokenType::NIL },
        { "or",     TokenType::OR },
        { "print",  TokenType::PRINT },
        { "return", TokenType::RETURN },
        { "super",  TokenType::SUPER },
        { "this",   TokenType::THIS },
        { "true",   TokenType::TRUE },
        { "var",    TokenType::VAR },
        { "while",  TokenType::WHILE },
};


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
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>':
            addToken(match('=') ? TokenType::GREATER : TokenType::GREATER_EQUAL); break;
        case '/': {
            if (match('/')) {
                //A comment goes to the end of the line
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        }
        case ' ':
        case '\r':
        case '\t':
            //Ignore whitespace
            break;
        case '\n':
            line++;
            break;
        case '"': string(); break;

        default:
            if(isDigit(c)){
                number();
            }
            else if(isAlpha(c)){
                identifier();
            }
            else {
                LoxError::error(line, "Unexpected character.");
            }
            break;
    }
}

void Scanner::identifier() {
    while(isAlphaNumeric(peek())) advance();

    std::string_view text = source.substr(start, current - start);
    auto it = keywords.find(text);
    TokenType type = TokenType::IDENTIFIER;
    if(it != keywords.end()) type = it->second;

    addToken(type);
}

void Scanner::number() {
    while(isDigit(peek())) advance();

    //Look for fractional part
    if(peek() == '.' && isDigit(peekNext())) {
        //Consume the '.'
        advance();

        while (isDigit(peek())) advance();
    }

    double num = 0;
    std::from_chars(source.data() + start, source.data() + current, num);

    addToken(TokenType::NUMBER, num);
}

void Scanner::string() {
    while(peek() != '"' && !isAtEnd()){
        if(peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()){
        LoxError::error(line, "Unterminated string");
        return;
    }

    //The closing "
    advance();

    //Trim surrounding quotes
    std::string_view value = source.substr(start + 1, current - start - 1);
    addToken(TokenType::STRING, value);
}

//check if next character is expected before consuming it
bool Scanner::match(char expected){
    if(isAtEnd()) return false;
    if(source.at(current) != expected) return false;

    current++;
    return true;
}

//look at the next character
char Scanner::peek(){
    if(isAtEnd()) return '\0';
    return source.at(current);
}

char Scanner::peekNext() {
    if(current + 1 >= source.length()) return '\0';
    return source.at(current + 1);
}

bool Scanner::isAlpha(char c) {
    return  (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c == '_');
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Scanner::isAlphaNumeric(char c) {
    return (isAlpha(c) || isDigit(c));
}

//look at and consume the next character
char Scanner::advance() {
    return source.at(current++);
}

void Scanner::addToken(TokenType type) {
    addToken(type, std::monostate{});
}

void Scanner::addToken(TokenType type, std::variant<double, std::string_view, std::monostate> literal) {
    std::string_view text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
}