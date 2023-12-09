#pragma once
#include <unordered_map>
#include <string>
#include "types.hpp"


std::unordered_map<std::string, Function> build_namespace();

Value *add(size_t argc, Value**args);
Value *subtract(size_t argc, Value**args);
Value *mul(size_t argc, Value**args);
Value *divide(size_t argc, Value**args);
