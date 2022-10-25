#include <fmt/format.h>

#include "debug.hpp"
#include "value.hpp"

void disassembleChunk(Chunk &chunk, std::string_view name) {
    fmt::print("== {} ==\n", name);

    for(int offset = 0; offset < chunk.code.size();){
        offset = disassembleInstruction(chunk, offset);
    }
}

static int simpleInstruction(std::string_view name, int offset){
    fmt::print("{:s}\n", name);
    return offset + 1;
}

static int constantInstruction(std::string_view name, Chunk& chunk, int offset){
    uint8_t constant = chunk.code.at(offset + 1);
    fmt::print("{:<16s} {:4d} '", name, constant);
    printValue(chunk.constants.at(constant));
    fmt::print("'\n");
    return offset + 2;
}

int disassembleInstruction(Chunk& chunk, int offset){
    fmt::print("{:04d} ", offset);

    if(offset > 0 && chunk.lines.at(offset) == chunk.lines.at(offset - 1)){
        fmt::print("   | ");
    }
    else{
        fmt::print("{:4d} ", chunk.lines.at(offset));
    }

    auto instruction = static_cast<OpCode>(chunk.code.at(offset));

    switch(instruction){
        case OpCode::RETURN:
            return simpleInstruction("OP_RETURN", offset);
        case OpCode::CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        default:
            fmt::print("Unknown opcode %d\n", (uint8_t)instruction);
            return offset + 1;
    }
}
