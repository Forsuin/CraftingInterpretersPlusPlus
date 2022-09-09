#pragma once

#include <string_view>

class LoxError {
public:
    static void error(int line, std::string_view message);
    static void report(int line, std::string_view where, std::string_view message);
};
