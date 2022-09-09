#include <iostream>
#include <format>


#include "loxError.hpp"
#include "lox.hpp"


void LoxError::error(int line, std::string_view message) {
    report(line, "", message);
}

void LoxError::report(int line, std::string_view where, std::string_view message) {
    std::cout << std::format("[line {}] Error{}: {}", line, where, message);
    Lox::hadError = true;
}