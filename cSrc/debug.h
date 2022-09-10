#pragma once
#ifndef CRAFTINGINTERPRETERS_DEBUG_H
#define CRAFTINGINTERPRETERS_DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif //CRAFTINGINTERPRETERS_DEBUG_H
