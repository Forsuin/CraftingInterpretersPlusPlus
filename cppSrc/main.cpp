#include <iostream>

#include "chunk.hpp"
#include "debug.hpp"
#include "vm.hpp"

int main(){
    Chunk chunk;

    int constant = chunk.addConstant(1.2);
    chunk.write(static_cast<uint8_t>(OpCode::CONSTANT), 123);
    chunk.write(constant, 123);

    chunk.write(static_cast<uint8_t>(OpCode::RETURN), 123);

    disassembleChunk(chunk, "test chunk");
    vm.interpret(chunk);

    return 0;
}