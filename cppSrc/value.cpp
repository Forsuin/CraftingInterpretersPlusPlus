#include <fmt/format.h>

#include "value.hpp"

void printValue(Value value){
    fmt::print("{:g}", value);
}