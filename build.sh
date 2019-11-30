bison parser.y -d
clang++ parser.tab.c scanner.cpp -o parser --std=c++11
