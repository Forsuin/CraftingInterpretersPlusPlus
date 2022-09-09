#include "scanner.hpp"
#include "loxError.hpp"

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
            addToken(match('=') ? TokenType::BANG_EQUAL : BANG); break;
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
            LoxError::error(line, "Unexpected character.");
            break;
    }
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

//look at and consume the next character
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