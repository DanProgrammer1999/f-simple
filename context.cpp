#include "context.h"

Context* Context::getDefaultContext() {
        auto res = new Context();
        res->functions = getDefaultFunctions();
        return res;
    }