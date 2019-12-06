bison parser.y -d
clang++ predefined_functions.cpp context.cpp function.cpp parser.cpp parser.tab.c scanner.cpp -o parser --std=c++11
