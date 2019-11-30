//
// Created by danieldv99 on 29/11/2019.
//

#ifndef F_SIMPLE_FUNCTION_H
#define F_SIMPLE_FUNCTION_H

#include <map>
#include <sstream>

#include "parser.h"
#include "errors.h"
#include "context.h"

typedef Element *(*FunctionPointer)(Context *, List *);

class Function : public Element {
protected:
    std::string name{};
    std::vector<std::string> *args;
    int args_number;
    bool lambda{false};

    Function(std::string name, std::vector<std::string> *args) :
            name(name), args(args), args_number(args->size()), execType() {};

public:
    // Context here so that predefined functions can access it
    virtual Element *eval(Context *currContext, List *args) {
        return nullptr;
    };

    void validate_args_number(int given_number) {
        if (given_number != this->args_number) {
            throw new ArgNumberMismatchException(this->name, given_number, this->args_number)
        }
    }

    void print() override {
        std::stringstream res;
        res << "<Function " << this->name << "(" << this->args << ")";
    }
};

// This class should be instantiated for predefined functions only
class PredefinedFunction : public Function {
private:
    FunctionPointer handler{};

public:
    PredefinedFunction(std::string name, std::vector<std::string> *args, FunctionPointer handler) :
            Function(name, args), handler(handler) {};

    Element *eval(Context *currContext, List *args) override {
        validate_args_number(args->elements.size());
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
        if (args->elements.size() != this->args_number) {
            throw new ArgNumberMismatchException(this->name, args->elements.size(), this->args_number);
        }
        auto local_context = currContext->copy();
        // Context MUST NOT be used here, need it because of override
        // arguments are already eval'd
        for(int i = 0; i < this->args->size(); i++){
            local_context->set(this->args[i], args->elements[i]);
        }


    }
};

class LambdaFunction : public CustomFunction {
public:
    LambdaFunction(std::vector<std::string> *args, std::vector<Element *> *body, Context *localContext) :
            CustomFunction("<lambda_func>", args, body, localContext) {
        this->lambda = true;
    };
};


#endif //F_SIMPLE_FUNCTION_H
