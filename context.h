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

    const std::map<std::string, Function *> &getFunctions() const {
        return functions;
    }

    bool has(std::string name) {
        auto elem = functions.find(name);
        return elem != functions.end();
    }

    Function *get(std::string name) {
        if (!has(name)) {
            return nullptr;
        }
        return functions[name];
    }

    Function *set(std::string name, Function *value) {
        Function *res = nullptr;
        if (has(name)) {
            res = functions[name];
        }

        functions[name] = value;

        return res;
    }

    Context *copy() {
        auto newContext = new Context();
        newContext->functions = this->functions;
        return newContext;
    }

    void print();
};


#endif //F_SIMPLE_CONTEXT_H
