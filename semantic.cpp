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

        // Special forms, keyword functions
        res["quote"] = quote;
        res["setq"] = setq;
        res["func"] = func;
        res["lambda"] = lambda;
        res["prog"] = prog;
        res["cond"] = cond;
        res["while"] = f_while;
        res["return"] = f_return;
        res["break"] = f_break;
        
        // Arithmetic functions
        res["plus"] = plus;
        res["minus"] = minus;
        res["times"] = times;
        res["divide"] = divide;
        
        // List operations
        res["head"] = head;
        res["tail"] = tail;
        res["cons"] = cons;

        // Comparisons
        res["equal"] = equal;
        res["nonequal"] = nonequal;
        res["less"] = less;
        res["lesseq"] = lesseq;
        res["greater"] = greater;
        res["greatereq"] = greatereq;

        // Predicates
        res["isint"] = isint;
        res["isreal"] = isreal;
        res["isbool"] = isbool;
        res["isnull"] = isnull;
        res["isatom"] = isatom;
        res["islist"] = islist;

        // Logical operators
        res["and"] = f_and;
        res["or"] = f_or;
        res["xor"] = f_xor;
        res["not"] = f_not;

        // Evaluator
        res["eval"] = eval;

        return res;
    }

private:
    // Take one argument and return it as it is
    static Element *quote(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // Return the argument itself
        return args->elements.front();
    }

    // Take two args (Atom, Element), evaluate second arg,
    // and create (update) entry in the context with name $1 to value $2
    static Element *setq(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] Set value of second argument to the first one

        // setq always returns null on success
        return new Nil();
    };

    // Takes three elements (Atom, List, Element): (name, args, body)
    // Store args and body, and add a name to the context
    static Element *func(Context *context, List *args) {
        if (args->elements.size() != 3) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] Save function name to context
    };

    // Takes two elements (List, Element): (args, body)
    // Store args and body, evaluate lambda function
    static Element *lambda(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] ???
    };

    // Takes two elements (List, Element): (context, atoms)
    // Sequentially evaluate atoms using given context
    static Element *prog(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] Using context call eval() for each element sequentially
    };

    // Takes two (or three) elements: (condition, body1, body2)
    // Conditional statement
    static Element *cond(Context *context, List *args) {
        if (args->elements.size() != 2 && args->elements.size() != 3) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] Evaluate condition, evaluate other parts if necessary
    };

    // Takes two elements: (condition, body)
    // Loop statement, calculate condition in loop, then execute body if true
    static Element *f_while(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one element
    // and returns it as the result of function (only used in functions)
    static Element *f_return(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Do not has any arguments,
    // Just interupts a loop
    static Element *f_break(Context *context, List *args) {
        if (args->elements.size() != 0) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Evaluation] 
    };

    // Takes two real or int elements,
    // Returns their sum
    static Element *plus(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two real or int elements,
    // Returns their difference
    static Element *minus(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two real or int elements,
    // Returns their multiplication
    static Element *times(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two real or int elements, 
    // Returns their division
    static Element *divide(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes list, returns its first element
    static Element *head(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes list, returns itself without first element
    static Element *tail(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // First arg can be any type, second is a list,
    // Returns list (second arg) with new first element - first arg
    static Element *cons(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of same type of int, real or bool,
    // Returns true if elements are equal, false otherwise
    static Element *equal(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of same type of int, real or bool,
    // Returns true if elements are not equal, false otherwise
    static Element *nonequal(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is less than second, false otherwise
    static Element *less(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is less or equal to second, false otherwise
    static Element *lesseq(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is greater than second, false otherwise
    static Element *greater(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is greater or equal to second, false otherwise
    static Element *greatereq(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one argument, returns true if it is integer,
    // Or false, otherwise
    static Element *isint(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one argument, returns true if it is real,
    // Or false, otherwise
    static Element *isreal(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one argument, returns true if it is boolean,
    // Or false, otherwise
    static Element *isbool(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one argument, returns true if it is null,
    // Or false, otherwise
    static Element *isnull(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one argument, returns true if it is an atom,
    // Or false, otherwise
    static Element *isatom(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one argument, returns true if it is a list,
    // Or false, otherwise
    static Element *islist(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of type boolean,
    // Returns result of logical and as boolean
    static Element *f_and(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of type boolean,
    // Returns result of logical or as boolean
    static Element *f_or(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of type boolean,
    // Returns result of logical xor as boolean
    static Element *f_xor(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes two elements of type boolean,
    // Returns result of logical negation as boolean
    static Element *f_not(Context *context, List *args) {
        if (args->elements.size() != 2) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };

    // Takes one element as argument,
    // If it is list - return result of its evaluation
    // Otherwise, just return 
    static Element *eval(Context *context, List *args) {
        if (args->elements.size() != 1) {
            // [TODO: Exceptions] Args number mismatch exception
        }

        // [TODO: Exceptions] Check that arguments are of correct types
            // [TODO: Exceptions] Type mismatch exception

        // [TODO: Evaluation] 
    };
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

<<<<<<< HEAD
<<<<<<< HEAD
    FunctionPointer set(std::string name, FunctionPointer value) {
        FunctionPointer res = nullptr;
        if (has(name)) {
=======
    FunctionPointer set(std::string name, FunctionPointer value){
        FunctionPointer res = nullptr;
        if(has(name)){
>>>>>>> basic functionality for context class
=======
    FunctionPointer set(std::string name, FunctionPointer value) {
        FunctionPointer res = nullptr;
        if (has(name)) {
>>>>>>> feat: base for class Function
            res = functions[name];
        }

        functions[name] = value;

        return res;
    }

<<<<<<< HEAD
<<<<<<< HEAD
    Context *copy() {
=======
    Context* copy(){
>>>>>>> basic functionality for context class
=======
    Context *copy() {
>>>>>>> feat: base for class Function
        auto newContext = new Context();
        // TODO will this make a copy?
        newContext->functions = functions;
        return newContext;
    }
};
