#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <format>

#include "lox.hpp"
#include "scanner.hpp"

bool Lox::hadError = false;

void Lox::main(int argc, char **argv) {

    if(argc > 2){
        std::cout << "Usage: jlox [script]" << std::endl;
        std::exit(64);
    }
    else if(argc == 2){
        runFile(argv[1]);
    }
    else{
        runPrompt();
    }
}

void Lox::runFile(std::string_view path) {
    run(readFile(path));

    if(hadError) std::exit(65);
}

void Lox::runPrompt() {
    std::string line;

    for(;;){
        std::cout << "> ";
        std::getline(std::cin, line);
        if(line.empty()) break;
        run(line);
        hadError = false;
    }
}

void Lox::run(std::string_view source) {
    Scanner scanner(source);
    std::span<Token> tokens = scanner.scanTokens();

    for(Token t : tokens){
        std::cout << t.toString() << std::endl;
    }
}



std::string_view Lox::readFile(std::string_view path) {
    constexpr auto readSize = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    auto out = std::string();
    auto buf = std::string(readSize, '\0');

    while(stream.read(&buf[0], readSize)){
        out.append(buf, 0, stream.gcount());
    }

    out.append(buf, 0, stream.gcount());
    return out;
}


