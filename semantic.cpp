#include <map>

#include "parser.h"
#include "errors.cpp"

class Function;

class Context;

typedef Element *(*FunctionPointer)(Context *, Elements *);

class DefaultFunctions {
public:
    // quote setq func lambda prog cond while return break
    static std::map<std::string, FunctionPointer> getDefaultFunctions() {
        std::map<std::string, FunctionPointer> res;
        res["quote"] = quote;
        res["setq"] = setq;

//        res["func"] = func;
//        res["lambda"] = lambda;
//        res["prog"] = prog;
//        res["cond"] = cond;
//        res["while"] = while;

        // return and break here?

        return res;
    }

private:
    static Element *quote(Context *context, Elements *args) {
        // Takes exactly one arg
        if (args->size() > 1) {
            // args number mismatch exception
        }
        // Return the argument itself
        return args->front();
    }

    static Element *setq(Context *context, Elements *args) {
        if (args->size() > 2) {
            // args number mismatch exception
        }

        // check if args.get(0) is Atom

        // evaluate args.get(1)

        // setq always returns null on success
        return new Nil();
    };

    // TODO define other functions
};

class Context {
private:
    Context() = default;

    std::map<std::string, FunctionPointer> functions;

public:

    static Context *getDefaultContext() {
        auto res = new Context();
        res->functions = DefaultFunctions::getDefaultFunctions();
        return res;
    }

    const std::map<std::string, FunctionPointer> &getFunctions() const {
        return functions;
    }
};
