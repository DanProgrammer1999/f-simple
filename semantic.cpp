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
protected:
    std::string name{};
    std::vector<std::string> *args;
    int args_number;
    bool lambda{false};

    Function(std::string name, std::vector<std::string> *args) :
            name(name), args(args), args_number(args->size()) {};

    // Context here so that predefined functions can access it
    virtual Element *eval(Context *currContext, List *args) {
        return nullptr;
    };

    bool validate_args_number(int given_number) {
        return given_number == this->args_number;
    }

    // # TODO write print method
    void print() override {
    }
};


// This class should be instantiated for predefined functions only
class PredefinedFunction : public Function {
private:
    FunctionPointer handler{};

public:
    PredefinedFunction(std::string name, std::vector<std::string> *args, Context *context, FunctionPointer handler) :
            Function(name, args), handler(handler) {};

    Element *eval(Context *currContext, List *args) override {
        return this->handler(currContext, args);
    }
};

class CustomFunction : public Function {
protected:
    std::vector<Element *> *body;
    Context *localContext;
public:
    CustomFunction(std::string name, std::vector<std::string> *args, std::vector<Element *> *body,
                   Context *localContext) : Function(name, args), body(body), localContext(localContext) {};

    Element *eval(Context *currContext, List *args) override {

        // Context MUST NOT be used here, need it because of override
        // TODO implement this (using predefined eval probably)
        this->localContext.get()
    }
};

class LambdaFunction : public CustomFunction {
    LambdaFunction(std::vector<std::string> *args, std::vector<Element *> *body, Context *localContext):
                CustomFunction("<lambda_func>", args, body, localContext), lambda(true){};
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
