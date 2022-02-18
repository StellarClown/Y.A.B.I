cmake_minimum_required (VERSION 3.8)

project ("YABI")
include_directories(lib)

add_executable (YABI "YABI.cpp" "lib/BfInterpreter.cpp" "lib/BfInterpreter.h")
