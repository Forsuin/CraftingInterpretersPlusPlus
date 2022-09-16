#pragma once
#ifndef CRAFTINGINTERPRETERS_COMPILER_H
#define CRAFTINGINTERPRETERS_COMPILER_H

#include "vm.h"
#include "object.h"

bool compile(const char* source, Chunk* chunk);

#endif //CRAFTINGINTERPRETERS_COMPILER_H
