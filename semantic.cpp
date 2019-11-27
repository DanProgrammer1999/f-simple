#include <map>

#include "parser.h"
#include "errors.cpp"

class Function;

class Context;

typedef Element* (*FunctionPointer)(Context *, Elements *);

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
    // Take one argument and return it as it is
    static Element* quote(Context *context, Elements *args){
        if(args->size() > 1){
            // args number mismatch exception
        }
        // Return the argument itself
        return args->front();
    }

    // Take two args (Atom, Element), evaluate second arg,
    // and create (update) entry in the context with name $1 to value $2
    static Element* setq(Context *context, Elements *args) {
        if(args->size() > 2){
            // args number mismatch exception
        }

        // check if args.get(0) is Atom

        // evaluate args.get(1)

        // setq always returns null on success
        return new Nil();
    };

    // Takes three elements (Atom, List, Element): (name, args, body)
    // store args and body, and add a name to the context
    static Element* func(Context *context, Elements *args){

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

    bool has(std::string name){
        auto elem = functions.find(name);
        return elem != functions.end();
    }

    FunctionPointer get(std::string name){
        if(!this->has(name)){
            return nullptr;
        }
        return functions[name];
    }

    FunctionPointer set(std::string name, FunctionPointer value){
        FunctionPointer res = nullptr;
        if(has(name)){
            res = functions[name];
        }

        functions[name] = value;

        return res;
    }

    Context* copy(){
        auto newContext = new Context();
        // TODO will this make a copy?
        newContext->functions = functions;
        return newContext;
    }
};
