#include <map>

#include "parser.h"
#include "errors.cpp"

class Context;

typedef Element *(*FunctionPointer)(Context *, List *);

class DefaultFunctions {
public:
    // quote setq func lambda prog cond while return break
    static std::map<std::string, FunctionPointer> getDefaultFunctions() {
        std::map<std::string, FunctionPointer> res;
        res["quote"] = quote;
        res["setq"] = setq;
        res["func"] = func;

//        res["lambda"] = lambda;
//        res["prog"] = prog;
//        res["cond"] = cond;
//        res["while"] = while;

        // return and break here?

        return res;
    }

private:
    // Take one argument and return it as it is
    static Element *quote(Context *context, List *args) {
        if (args->elements.size() > 1) {
            // args number mismatch exception
        }
        // Return the argument itself
        return args->elements.front();
    }

    // Take two args (Atom, Element), evaluate second arg,
    // and create (update) entry in the context with name $1 to value $2
    static Element *setq(Context *context, List *args) {
        if (args->elements.size() > 2) {
            // args number mismatch exception
        }

        // check if args.get(0) is Atom

        // evaluate args.get(1)

        // setq always returns null on success
        return new Nil();
    };

    // Takes three elements (Atom, List, Element): (name, args, body)
    // store args and body, and add a name to the context
    static Element *func(Context *context, List *args) {

    };
    // TODO define other functions
};

class Function : public Element {
private:
    std::string name{};
    std::vector<std::string> *args{};
    Element *body;

public:
    Function(Atom *name, List *args, Element *body): body(body) {
        if(name != nullptr && !name->identifier.empty()){
            this->name = name->identifier;
        }
        // else it is nullptr by default

        for(auto elem: args->elements) {
            try {
                Atom *arg = (Atom *) elem;
                this->args->push_back(arg->identifier);
            }
            catch (std::exception &) {
                // invalid element type exception, must be atom
            }
        }
    }

    Element eval(Context* context, List *args){
        // if body is literal, simply return its value

        // else if body is atom, try to look it up in context dict, and throw exception if does not exist
        // but not good approach, since should bind the function to value in context when declared, not when called,
        // as context may change
        // better resolve value of literal before creating a function

        // if it's a list, create new context (copy), execute statements one by one, return result.
    }

    // # TODO maybe?
    void print() override {}
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

    bool has(std::string name) {
        auto elem = functions.find(name);
        return elem != functions.end();
    }

    FunctionPointer get(std::string name) {
        if (!has(name)) {
            return nullptr;
        }
        return functions[name];
    }

    FunctionPointer set(std::string name, FunctionPointer value) {
        FunctionPointer res = nullptr;
        if (has(name)) {
            res = functions[name];
        }

        functions[name] = value;

        return res;
    }

    Context *copy() {
        auto newContext = new Context();
        // TODO will this make a copy?
        newContext->functions = functions;
        return newContext;
    }
};
