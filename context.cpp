#include "context.h"

Context::Context() {
        this->functions = getDefaultFunctions();
    }

void Context::print(){
    for(auto it = this->functions.cbegin(); it != this->functions.cend(); ++it){
            std::cout << it->first << " " << it->second->toString() << "\n";
    }
}