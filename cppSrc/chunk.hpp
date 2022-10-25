#pragma once

#include <cstdint>
#include <vector>

#include "value.hpp"

enum struct OpCode{
    CONSTANT,
    RETURN,
};

struct Chunk {
    std::vector<uint8_t> code;
    std::vector<Value> constants;
    std::vector<int> lines;

    void write(uint8_t byte, int line);
    int addConstant(Value value);
    [[nodiscard]] int size() const;
};
