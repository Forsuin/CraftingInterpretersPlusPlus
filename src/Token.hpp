#pragma once

#include <variant>
#include <format>

#include "tokenType.hpp"

class Token{
    const TokenType type;
    const std::string_view lexeme;
    const std::variant<double, std::string_view, std::monostate> literal;
    const int line;

public:
    Token(TokenType type, std::string_view lexeme, std::variant<double, std::string_view, std::monostate> literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}


    std::string toString() {
        if (std::holds_alternative<double>(literal)) {
            return std::format("{} {} {}", type.name, lexeme, std::get<double>(literal));
        }
        else if(std::holds_alternative<std::string_view>(literal)){
            return std::format("{} {} {}", type.name, lexeme, std::get<std::string_view>(literal));

        }
        else{
            return std::format("{} {} {}", type.name, lexeme, "NULL");

        }
    }
};