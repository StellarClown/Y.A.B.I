cmake_minimum_required (VERSION 3.8)

project ("YABI_test")
include_directories(lib)

add_executable (YABI_test "YABI_test.cpp" "lib/BfInterpreter.cpp" "lib/BfInterpreter.h")