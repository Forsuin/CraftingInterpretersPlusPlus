#pragma once

#include <vector>

#include "chunk.hpp"


enum class InterpretResult{
    OK,
    COMPILER_ERROR,
    RUNTIME_ERROR
};

struct VM {
    Chunk chunk;
    std::vector<Value> stack;

    InterpretResult interpret(Chunk& chunk);
    void push(Value value);
    Value pop();
};
