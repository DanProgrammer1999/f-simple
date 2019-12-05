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

class Context;


typedef Element *(*FunctionPointer)(Context *, List *);

class Function : public Element {
protected:
    std::string name{};
    std::vector<std::string> *args;
    int args_number;
    ExecutionType execType;

    Function(std::string name, std::vector<std::string> *args) :
            name(name), args(args), args_number(args->size()), execType(typeFunction) {};

public:
    bool predefined{false};
    bool lambda{false};

    // Context here so that predefined functions can access it
    virtual Element *eval(Context *currContext, List *args) {
        return nullptr;
    };

    void validate_args_number(int given_number) {
        if (given_number != this->args_number) {
            throw new ArgNumberMismatchException(this->name, given_number, this->args_number);
        }
    }

    std::string toString() override {
        std::stringstream res;
        res << "<Function " << this->name << "(";
        for(auto arg : *(this->args)){
            res << arg << ", ";
        } 
        res << ")>";
        return res.str();
    }
};

// This class should be instantiated for predefined functions only
class PredefinedFunction : public Function {
private:
    FunctionPointer handler{};

public:
    PredefinedFunction(std::string name, std::vector<std::string> *args, FunctionPointer handler) :
            Function(name, args), handler(handler){
        this->predefined = true;
    };

    Element *eval(Context *currContext, List *args) override {
        if (args->elements.size() != this->args_number) {
            std::cout << "WHYYY: " << args->toString() << "\n";
            throw ArgNumberMismatchException(this->name, args->elements.size(), this->args_number);
        }        
        std::cout << "Called predefined function " << this->name << std::endl;
        return this->handler(currContext, args);
    }
};

class CustomFunction : public Function {
protected:
    List *body;
    Context *localContext;
public:
    CustomFunction(std::string name, std::vector<std::string> *args, List *body,
                   Context *localContext) : Function(name, args), localContext(localContext) {

        this->body = body;
    };

    Element *eval(Context *currContext, List *args) override;
};

class LambdaFunction : public CustomFunction {
public:
    LambdaFunction(std::vector<std::string> *args, List *body, Context *localContext) :
            CustomFunction("<lambda_func>", args, body, localContext) {
        this->lambda = true;
    };
};


#endif //F_SIMPLE_FUNCTION_H
