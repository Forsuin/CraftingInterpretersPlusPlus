#pragma once
#ifndef CRAFTINGINTERPRETERS_CHUNK_H
#define CRAFTINGINTERPRETERS_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum{
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    int* lines;
    ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
void freeChunk(Chunk* chunk);

#endif //CRAFTINGINTERPRETERS_CHUNK_H