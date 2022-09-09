#pragma once

#include <string_view>


class Lox {
public:
    static void main(int argc, char* argv[]);

private:
    static bool hadError;


    static void runFile(std::string_view path);
    static void runPrompt();
    static std::string_view readFile(std::string_view path);
    static void run(std::string_view source);


};
