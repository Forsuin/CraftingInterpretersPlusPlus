#include "chunk.hpp"

void Chunk::write(uint8_t byte, int line) {
    code.push_back(byte);
    lines.push_back(line);
}

int Chunk::size() const{
    return code.size();
}

int Chunk::addConstant(Value value) {
    constants.push_back(value);
    return constants.size() - 1;
}
