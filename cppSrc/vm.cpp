#include <fmt/format.h>

#include "vm.hpp"
#include "common.h"
#include "debug.hpp"
#include "value.hpp"

VM vm;


static InterpretResult run() {
    auto ip = vm.chunk.code.begin();
    for(;;){
#ifdef DEBUG_TRACE_EXECUTION
        fmt::print("          ");
        for(Value val : vm.stack){
            fmt::print("[ ");
            printValue(val);
            fmt::print(" ]");
        }
        fmt::print("\n");
        disassembleInstruction(vm.chunk, (int)*ip);
#endif
        uint8_t instruction;
        switch (instruction = *ip++) {
            case static_cast<int>(OpCode::CONSTANT): {
                Value constant = vm.chunk.constants.at(*ip++);
                vm.push(constant);
                printValue(constant);
                fmt::print("\n");
                break;
            }
            case static_cast<int>(OpCode::RETURN):
                printValue(vm.pop());
                fmt::print("\n");
                return InterpretResult::OK;
        }
    }
}

InterpretResult VM::interpret(Chunk &chunk) {
    vm.chunk = chunk;
    return run();

}

void VM::push(Value value) {
    stack.push_back(value);
}


Value VM::pop() {
    Value val = stack.back();
    stack.pop_back();
    return val;
}
