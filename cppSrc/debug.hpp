#pragma once
#ifndef CRAFTINGINTERPRETERS_DEBUG_HPP
#define CRAFTINGINTERPRETERS_DEBUG_HPP

#include <xstring>
#include "chunk.hpp"

void disassembleChunk(Chunk& chunk, std::string_view name);
int disassembleInstruction(Chunk& chunk, int offset);

#endif //CRAFTINGINTERPRETERS_DEBUG_HPP
