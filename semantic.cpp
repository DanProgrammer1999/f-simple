#include <map>

#include "semantic.h"
#include "parser.h"
#include "errors.h"

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

    void validate_args_number(int given_number) {
        if (given_number != this->args_number) {
            throw new ArgNumberMismatchException(this->name, given_number, this->args_number)
        }
    }

    // # TODO write print method
    void print() override {
        std::stringstream res;
        res <<
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

        // Context MUST NOT be used here, need it because of override
        // TODO implement this (using predefined eval probably)
        for (auto item : args->elements) {

        }
    }
};

class LambdaFunction : public CustomFunction {
    LambdaFunction(std::vector<std::string> *args, std::vector<Element *> *body, Context *localContext) :
            CustomFunction("<lambda_func>", args, body, localContext) {
        this->lambda = true;
    };
};

class DefaultFunctions {
public:
    // quote setq func lambda prog cond while return break
    static std::map<std::string, Function *> getDefaultFunctions() {
        std::map<std::string, Function *> res;
        // Special forms, keyword functions
        res["quote"] = new PredefinedFunction("quote", new std::vector<std::string>{"element"}, quote);
        res["setq"] = new PredefinedFunction("setq", new std::vector<std::string>{"atom", "element"}, setq);
        res["func"] = new PredefinedFunction("func", new std::vector<std::string>{"atom", "list", "element"}, func);
        res["lambda"] = new PredefinedFunction("lambda", new std::vector<std::string>{"list", "element"}, lambda);
        res["prog"] = new PredefinedFunction("prog", new std::vector<std::string>{"list", "element"}, prog);
        res["cond"] = new PredefinedFunction("cond", new std::vector<std::string>{"if-cond", "then-body", "else-body"},
                                             cond);
        res["while"] = new PredefinedFunction("while", new std::vector<std::string>{"loop-cond", "body"}, f_while);
        res["return"] = new PredefinedFunction("return", new std::vector<std::string>{"element"}, f_return);
        res["break"] = new PredefinedFunction("break", new std::vector<std::string>{}, f_break);

        // Arithmetic functions
        res["plus"] = new PredefinedFunction("plus", new std::vector<std::string>{"element1", "element2"}, plus);
        res["minus"] = new PredefinedFunction("minus", new std::vector<std::string>{"element1", "element2"}, minus);
        res["times"] = new PredefinedFunction("times", new std::vector<std::string>{"element1", "element2"}, times);
        res["divide"] = new PredefinedFunction("divide", new std::vector<std::string>{"element1", "element2"}, divide);

        // List operations
        res["head"] = new PredefinedFunction("head", new std::vector<std::string>{"element"}, head);
        res["tail"] = new PredefinedFunction("tail", new std::vector<std::string>{"element"}, tail);
        res["cons"] = new PredefinedFunction("cons", new std::vector<std::string>{"element-to-cons", "list"}, cons);

        // Comparisons
        res["equal"] = new PredefinedFunction("equal", new std::vector<std::string>{"element1", "element2"}, equal);
        res["nonequal"] = new PredefinedFunction("nonequal", new std::vector<std::string>{"element1", "element2"},
                                                 nonequal);
        res["less"] = new PredefinedFunction("less", new std::vector<std::string>{"element1", "element2"}, less);
        res["lesseq"] = new PredefinedFunction("lesseq", new std::vector<std::string>{"element1", "element2"}, lesseq);
        res["greater"] = new PredefinedFunction("greater", new std::vector<std::string>{"element1", "element2"},
                                                greater);
        res["greatereq"] = new PredefinedFunction("greatereq", new std::vector<std::string>{"element1", "element2"},
                                                  greatereq);

        // Predicates
        res["isint"] = new PredefinedFunction("isint", new std::vector<std::string>{"element"}, isint);
        res["isreal"] = new PredefinedFunction("isreal", new std::vector<std::string>{"element"}, isreal);
        res["isbool"] = new PredefinedFunction("isbool", new std::vector<std::string>{"element"}, isbool);
        res["isnull"] = new PredefinedFunction("isnull", new std::vector<std::string>{"element"}, isnull);
        res["isatom"] = new PredefinedFunction("isatom", new std::vector<std::string>{"element"}, isatom);
        res["islist"] = new PredefinedFunction("islist", new std::vector<std::string>{"element"}, islist);

        // Logical operators
        res["and"] = new PredefinedFunction("and", new std::vector<std::string>{"element1", "element2"}, f_and);
        res["or"] = new PredefinedFunction("or", new std::vector<std::string>{"element1", "element2"}, f_or);
        res["xor"] = new PredefinedFunction("xor", new std::vector<std::string>{"element1", "element2"}, f_xor);
        res["not"] = new PredefinedFunction("not", new std::vector<std::string>{"element"}, f_not);

        // Evaluator
        res["eval"] = new PredefinedFunction("eval", new std::vector<std::string>{"element"}, eval);

        // Constants
        res["nil"] = new PredefinedFunction("nil", new std::vector<std::string>{}, nil);
        res["true"] = new PredefinedFunction("true", new std::vector<std::string>{}, f_true);
        res["false"] = new PredefinedFunction("false", new std::vector<std::string>{}, f_false);

        return res;
    }

private:
    // Take one argument and return it as it is
    static Element *quote(Context *context, List *args) {
        // Return the argument itself
        return args->elements.front();
    }

    // Take two args (Atom, Element), evaluate second arg,
    // and create (update) entry in the context with name $1 to value $2
    static Element *setq(Context *context, List *args) {
        if (args->elements[0]->getExecType() != typeAtom) {
            throw new TypeMismatchException("setq", toString(args->elements[0]->getExecType(), toString(typeAtom)));
        }

        // [TODO: Evaluation] Set value of second argument to the first one
    }


    // Takes three elements (Atom, List, Element): (name, args, body)
    // Store args and body, and add a name to the context
    static Element *func(Context *context, List *args) {
        if (args->elements[0]->getExecType() != typeAtom) {
            throw new TypeMismatchException("func", toString(args->elements[0]->getExecType()), toString(typeAtom));
        }

        if (args->elements[1]->getExecType() != typeList) {

        }

        // [TODO: Evaluation] Save function name to context
    }

    // Takes two elements (List, Element): (args, body)
    // Store args and body, evaluate lambda function
    static Element *lambda(Context *context, List *args) {
        if (args->elements[0]->getExecType() != typeList) {
            throw new TypeMismatchException("lambda", toString(args->elements[0]->getExecType()), toString(typeList))
        }

        // [TODO: Evaluation] ???
    }

    // Takes two elements (List, Element): (context, atoms)
    // Sequentially evaluate atoms using given context
    // Do we need it ???
    static Element *prog(Context *context, List *args) {
        if (args->elements[0]->getExecType() != typeList) {
            throw new TypeMismatchException("prog", toString(args->elements[0]->getExecType()), toString(typeList))
        }

        // [TODO: Evaluation] Using context call eval() for each element sequentially
    }

    // Takes two (or three) elements: (condition, body1, body2)
    // Conditional statement
    static Element *cond(Context *context, List *args) {
        // [TODO: Evaluation] Evaluate condition, evaluate other parts if necessary
    }

    // Takes two elements: (condition, body)
    // Loop statement, calculate condition in loop, then execute body if true
    static Element *f_while(Context *context, List *args) {
        // [TODO: Evaluation] 
    }

    // Takes one element
    // and returns it as the result of function (only used in functions)
    static Element *f_return(Context *context, List *args) {
        // [TODO: Evaluation] 
    }

    // Do not has any arguments,
    // Just interupts a loop
    static Element *f_break(Context *context, List *args) {
        // [TODO: Evaluation] 
    }

    // Takes two real or int elements,
    // Returns their sum
    static Element *plus(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("plus", "Cannot compare arguments with different types");
        }

        if (a->getExecType() == typeInteger) {
            return new Integer(((Integer *) a)->value + ((Integer *) b)->value);
        } else if (a->getExecType() == typeReal) {
            return new Real(((Real *) a)->value + ((Real *) b)->value);
        } else {
            throw new TypeMismatchException("plus", toString(a->getExecType()), toString("Integer or Real"));
        }
    }

    // Takes two real or int elements,
    // Returns their difference
    static Element *minus(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("minus", "Cannot compare arguments with different types");
        }

        if (a->getExecType() == typeInteger) {
            return new Integer(((Integer *) a)->value - ((Integer *) b)->value);
        } else if (a->getExecType() == typeReal) {
            return new Real(((Real *) a)->value - ((Real *) b)->value);
        } else {
            throw new TypeMismatchException("minus", toString(a->getExecType()), toString("Integer or Real"));
        }
    }

    // Takes two real or int elements,
    // Returns their multiplication
    static Element *times(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("times", "Cannot compare arguments with different types");
        }

        if (a->getExecType() == typeInteger) {
            return new Integer(((Integer *) a)->value * ((Integer *) b)->value);
        } else if (a->getExecType() == typeReal) {
            return new Real(((Real *) a)->value * ((Real *) b)->value);
        } else {
            throw new TypeMismatchException("times", toString(a->getExecType()), toString("Integer or Real"));
        }
    }

    // Takes two real or int elements, 
    // Returns their division
    static Element *divide(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("divide", "Cannot compare arguments with different types");
        }

        if (a->getExecType() == typeInteger) {
            return new Integer(((Integer *) a)->value / ((Integer *) b)->value);
        } else if (a->getExecType() == typeReal) {
            return new Real(((Real *) a)->value / ((Real *) b)->value);
        } else {
            throw new TypeMismatchException("divide", toString(a->getExecType()), toString("Integer or Real"));
        }
    }

    // Takes list, returns its first element
    static Element *head(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));

        if (a->getExecType() != typeList) {
            throw new TypeMismatchException("head", toString(a->getExecType()), toString(typeList))
        }

        return new Element(*(((List *) a)->elements[0]));
    }

    // Takes list, returns itself without first element
    static Element *tail(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));

        if (a->getExecType() != typeList) {
            throw new TypeMismatchException("tail", toString(a->getExecType()), toString(typeList))
        }

        List *res = new List();
        List *a_list = (List *) a;

        for (int i = 1; i < a_list->elements.size(); i++) {
            res->elements.push_back(a_list->elements[i]);
        }

        return res;
    }

    // First arg can be any type, second is a list,
    // Returns list (second arg) with new first element - first arg
    static Element *cons(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{a})));

        if (b->getExecType() != typeList) {
            throw new TypeMismatchException("cons", toString(b->getExecType()), toString(typeList))
        }

        List *res = new List();
        List *b_list = (List *) b;

        res->elements.push_back(a);
        for (auto element : b_list->elements) {
            res->elements.push_back(element);
        }

        return res;
    }

    // Takes two elements of same type of int, real or bool,
    // Returns true if elements are equal, false otherwise
    static Element *equal(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("equal", "Cannot compare arguments with different types");
        }

        switch (a->getExecType()) {
            case typeBoolean:
                return new Boolean(((Boolean *) a)->value == ((Boolean *) b)->value);
            case typeInteger:
                return new Boolean(((Integer *) a)->value == ((Integer *) b)->value);
            case typeReal:
                return new Boolean(((Real *) a)->value == ((Real *) b)->value);
            default:
                throw new TypeMismatchException("equal", toString(a->getExecType()), toString("Literal"));
        }
    }

    // Takes two elements of same type of int, real or bool,
    // Returns true if elements are not equal, false otherwise
    static Element *nonequal(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("nonequal", "Cannot compare arguments with different types");
        }

        switch (a->getExecType()) {
            case typeBoolean:
                return new Boolean(((Boolean *) a)->value != ((Boolean *) b)->value);
            case typeInteger:
                return new Boolean(((Integer *) a)->value != ((Integer *) b)->value);
            case typeReal:
                return new Boolean(((Real *) a)->value != ((Real *) b)->value);
            default:
                throw new TypeMismatchException("nonequal", toString(a->getExecType()), toString("Literal"));
        }
    }

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is less than second, false otherwise
    static Element *less(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("less", "Cannot compare arguments with different types");
        }

        switch (a->getExecType()) {
            case typeBoolean:
                return new Boolean(((Boolean *) a)->value < ((Boolean *) b)->value);
            case typeInteger:
                return new Boolean(((Integer *) a)->value < ((Integer *) b)->value);
            case typeReal:
                return new Boolean(((Real *) a)->value < ((Real *) b)->value);
            default:
                throw new TypeMismatchException("less", toString(a->getExecType()),
                                                toString("Literal (number or bool)"));
        }
    }

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is less or equal to second, false otherwise
    static Element *lesseq(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("lesseq", "Cannot compare arguments with different types");
        }
        switch (a->getExecType()) {
            case typeBoolean:
                return new Boolean(((Boolean *) a)->value <= ((Boolean *) b)->value);
            case typeInteger:
                return new Boolean(((Integer *) a)->value <= ((Integer *) b)->value);
            case typeReal:
                return new Boolean(((Real *) a)->value <= ((Real *) b)->value);
            default:
                throw new TypeMismatchException("lesseq", toString(a->getExecType()),
                                                toString("Literal (number or bool)"));
        }
    }

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is greater than second, false otherwise
    static Element *greater(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("greater", "Cannot compare arguments with different types");
        }

        switch (a->getExecType()) {
            case typeBoolean:
                return new Boolean(((Boolean *) a)->value > ((Boolean *) b)->value);
            case typeInteger:
                return new Boolean(((Integer *) a)->value > ((Integer *) b)->value);
            case typeReal:
                return new Boolean(((Real *) a)->value > ((Real *) b)->value);
            default:
                throw new TypeMismatchException("greater", toString(a->getExecType()),
                                                toString("Literal (number or bool)"));
        }
    }

    // Takes two elements of same type of int, real or bool,
    // Returns true if first element is greater or equal to second, false otherwise
    static Element *greatereq(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != b->getExecType()) {
            throw new CustomException("greatereq", "Cannot compare arguments with different types");
        }

        switch (a->getExecType()) {
            case typeBoolean:
                return new Boolean(((Boolean *) a)->value >= ((Boolean *) b)->value);
            case typeInteger:
                return new Boolean(((Integer *) a)->value >= ((Integer *) b)->value);
            case typeReal:
                return new Boolean(((Real *) a)->value >= ((Real *) b)->value);
            default:
                throw new TypeMismatchException("greatereq", toString(a->getExecType()),
                                                toString("Literal (number or bool)"));
        }
    }

    // Takes one argument, returns true if it is integer,
    // Or false, otherwise
    static Element *isint(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        if (a->getExecType() == typeInteger)
            return new Boolean(true);
        else
            return new Boolean(false);
    }

    // Takes one argument, returns true if it is real,
    // Or false, otherwise
    static Element *isreal(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        if (a->getExecType() == typeReal)
            return new Boolean(true);
        else
            return new Boolean(false);
    }

    // Takes one argument, returns true if it is boolean,
    // Or false, otherwise
    static Element *isbool(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        if (a->getExecType() == typeBoolean)
            return new Boolean(true);
        else
            return new Boolean(false);
    }

    // Takes one argument, returns true if it is null,
    // Or false, otherwise
    static Element *isnull(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        if (a->getExecType() == typeNil)
            return new Boolean(true);
        else
            return new Boolean(false);
    }

    // Takes one argument, returns true if it is an atom,
    // Or false, otherwise
    static Element *isatom(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        if (a->getExecType() == typeAtom)
            return new Boolean(true);
        else
            return new Boolean(false);
    }

    // Takes one argument, returns true if it is a list,
    // Or false, otherwise
    static Element *islist(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        if (a->getExecType() == typeList)
            return new Boolean(true);
        else
            return new Boolean(false);
    }

    // Takes two elements of type boolean,
    // Returns result of logical and as boolean
    static Element *f_and(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != typeBoolean) {
            throw new TypeMismatchException("and", toString(a->getExecType()), toString(typeBoolean))
        }

        if (b->getExecType() != typeBoolean) {
            throw new TypeMismatchException("and", toString(b->getExecType()), toString(typeBoolean))
        }

        return new Boolean(((Boolean *) a)->value & ((Boolean *) b)->value);
    }

    // Takes two elements of type boolean,
    // Returns result of logical or as boolean
    static Element *f_or(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != typeBoolean) {
            throw new TypeMismatchException("or", toString(a->getExecType()), toString(typeBoolean))
        }

        if (b->getExecType() != typeBoolean) {
            throw new TypeMismatchException("or", toString(b->getExecType()), toString(typeBoolean))
        }

        return new Boolean(((Boolean *) a)->value | ((Boolean *) b)->value);
    }

    // Takes two elements of type boolean,
    // Returns result of logical xor as boolean
    static Element *f_xor(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));
        Element *b = eval(context, new List(*(new Elements{b})));

        if (a->getExecType() != typeBoolean) {
            throw new TypeMismatchException("xor", toString(a->getExecType()), toString(typeBoolean))
        }

        if (b->getExecType() != typeBoolean) {
            throw new TypeMismatchException("xor", toString(b->getExecType()), toString(typeBoolean))
        }

        return new Boolean(((Boolean *) a)->value & ((Boolean *) b)->value);
    }

    // Takes element of type boolean,
    // Returns its logical negation as boolean
    static Element *f_not(Context *context, List *args) {
        Element *a = eval(context, new List(*(new Elements{a})));

        if (a->getExecType() != typeBoolean) {
            throw new TypeMismatchException("not", toString(a->getExecType()), toString(typeBoolean))
        }

        return new Boolean(!((Boolean *) a)->value);
    }

    // Takes one element as argument,
    // If it is list - return result of its evaluation
    // Otherwise, just return 
    static Element *eval(Context *context, List *args) {
        if (args->elements[0]->getExecType() != typeAtom) {
            throw new TypeMismatchException("eval", toString(args->elements[0]->getExecType()), toString(typeAtom));
        }

        // [TODO: Evaluation] 
    }

    static Element *nil(Context *context, List *args) {
        return Nil::getNil();
    }

    static Element *f_true(Context *context, List *args) {
        return new Boolean(true);
    }

    static Element *f_false(Context *context, List *args) {
        return new Boolean(false);
    }
};

class Context {
private:
    Context() = default;

    std::map<std::string, Function *> functions;

public:

    static Context *getDefaultContext() {
        auto res = new Context();
        res->functions = DefaultFunctions::getDefaultFunctions();
        return res;
    }

    const std::map<std::string, Function *> &getFunctions() const {
        return functions;
    }

    bool has(std::string name) {
        auto elem = functions.find(name);
        return elem != functions.end();
    }

    Function *get(std::string name) {
        if (!has(name)) {
            return nullptr;
        }
        return functions[name];
    }

    Function *set(std::string name, Function *value) {
        Function *res = nullptr;
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


