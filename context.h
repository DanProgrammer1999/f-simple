#ifndef F_SIMPLE_CONTEXT_H
#define F_SIMPLE_CONTEXT_H

#include "parser.h"
#include "function.h"

class Context {
private:
    Context() = default;

    std::map<std::string, Function *> functions;

public:

    static Context *getDefaultContext() {
        auto res = new Context();
        res->functions = GetDefaultFunctions();
        return res;
    }

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
        Function *res = Nil::getNil();
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
};


#endif //F_SIMPLE_CONTEXT_H
