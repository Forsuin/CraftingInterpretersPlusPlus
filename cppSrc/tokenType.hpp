#pragma once

#include <string_view>


class TokenType{
public:
    // Single-character tokens.
    static const TokenType LEFT_PAREN;
    static const TokenType RIGHT_PAREN;
    static const TokenType LEFT_BRACE;
    static const TokenType RIGHT_BRACE;

    static const TokenType COMMA;
    static const TokenType DOT;
    static const TokenType MINUS;
    static const TokenType PLUS;
    static const TokenType SEMICOLON;
    static const TokenType SLASH;
    static const TokenType STAR;


// One or two character tokens.
    static const TokenType BANG;
    static const TokenType BANG_EQUAL;

    static const TokenType EQUAL;
    static const TokenType EQUAL_EQUAL;

    static const TokenType GREATER;
    static const TokenType GREATER_EQUAL;

    static const TokenType LESS;
    static const TokenType LESS_EQUAL;


// Literals.
    static const TokenType IDENTIFIER;
    static const TokenType STRING;
    static const TokenType NUMBER;


// Keywords.
    static const TokenType AND;
    static const TokenType CLASS;
    static const TokenType ELSE;
    static const TokenType FALSE;
    static const TokenType FUN;
    static const TokenType FOR;
    static const TokenType IF;
    static const TokenType NIL;
    static const TokenType OR;

    static const TokenType PRINT;
    static const TokenType RETURN;
    static const TokenType SUPER;
    static const TokenType THIS;
    static const TokenType TRUE;
    static const TokenType VAR;
    static const TokenType WHILE;

#undef EOF

    static const TokenType EOF;

private:
    int index;

public:
    constexpr explicit TokenType(int index, std::string_view name) : index(index), name(name) {}
    constexpr operator int() const { return index; }

    std::string_view name;
};


