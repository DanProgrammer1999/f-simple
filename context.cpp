#include "context.h"

Context::Context() {
        this->functions = getDefaultFunctions();
    }

void Context::print(){
    for(auto it = this->functions.cbegin(); it != this->functions.cend(); ++it){
            std::cout << it->first << " " << it->second->toString() << "\n";
    }
}

bool Context::has(std::string name) {
    auto elem = functions.find(name);
    return elem != functions.end();
}

Function *Context::get(std::string name) {
    return functions[name];
}

Function *Context::set(std::string name, Function *value){
    Function *res = nullptr;
    if (has(name)) {
        res = functions[name];
    }

    functions[name] = value;

    return res;
}

Context *Context::copy(){
    auto newContext = new Context();
    newContext->functions = this->functions;
    return newContext;
}