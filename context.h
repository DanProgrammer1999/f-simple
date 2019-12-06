#ifndef F_SIMPLE_CONTEXT_H
#define F_SIMPLE_CONTEXT_H

#include "parser.h"
#include "function.h"
#include "predefined_functions.h"

class Function;

class Context {
private:
    std::map<std::string, Function *> functions;

public:
    Context();
    static Context *getDefaultContext();

    bool has(std::string name); 

    Function *get(std::string name);

    Function *set(std::string name, Function *value); 

    Context *copy();

    void print();
};


#endif //F_SIMPLE_CONTEXT_H
