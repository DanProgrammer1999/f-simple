#include "predefined_functions.h"

Element *quote(Context *context, List *args) {
    // Return the argument itself
    return args->elements.front();
}

// Take two args (Atom, Element), evaluate second arg,
// and create (update) entry in the context with name $1 to value $2
Element *setq(Context *context, List *args) {
    if (args->elements[0]->getExecType() != typeAtom) {
        throw TypeMismatchException("setq", toString(args->elements[0]->getExecType()), toString(typeAtom));
    }
    std::string name = Atom::fromElement(args->elements[0])->identifier;
    auto res = context->set(name, args->elements[2]);

    return res;
}


// Takes three elements (Atom, List, Element): (name, args, body)
// Store args and body, and add a name to the context
Element *func(Context *context, List *args) {
    if (args->elements[0]->getExecType() != typeAtom) {
        throw TypeMismatchException("func", toString(args->elements[0]->getExecType()), toString(typeAtom));
    }

    if (args->elements[1]->getExecType() != typeList) {
        throw TypeMismatchException("func", toString(args->elements[1]->getExecType()), toString(typeList));
    }

    std::string name = Atom::fromElement(args->elements[0])->identifier;
    std::vector<std::string> func_args;
    std::vector<Element *> body = ((List *) args->elements[2])->elements;

    for (Element *arg : ((List *) args->elements[1])->elements) {
        if (arg->getExecType() != typeAtom) {
            throw TypeMismatchException("func", toString(arg->getExecType()), toString(typeAtom));
        }
        func_args.push_back(Atom::fromElement(arg)->identifier);
    }

    auto function = new CustomFunction(name, &func_args, &body, context);
    auto res = context->set(name, function);

    return res;
}

// Takes two elements (List, Element): (args, body)
// Store args and body, evaluate lambda function
Element *lambda(Context *context, List *args) {
    if (args->elements[0]->getExecType() != typeList) {
        throw TypeMismatchException("lambda", toString(args->elements[0]->getExecType()), toString(typeList));
    }
    std::vector<std::string> func_args;
    std::vector<Element *> body = ((List *) args->elements[2])->elements;

    for (Element *arg : ((List *) args->elements[1])->elements) {
        if (arg->getExecType() != typeAtom) {
            throw TypeMismatchException("func", toString(arg->getExecType()), toString(typeAtom));
        }
        func_args.push_back(Atom::fromElement(arg)->identifier);
    }

    Function *function = new LambdaFunction(&func_args, &body, context);

    return function;
}

// Takes two elements (List, Element): (context, atoms)
// Sequentially evaluate atoms using given context
// Do we need it ???
Element *prog(Context *context, List *args) {
    if (args->elements[0]->getExecType() != typeList) {
        throw TypeMismatchException("prog", toString(args->elements[0]->getExecType()), toString(typeList));
    }

    // [TODO: Evaluation] Using context call eval() for each element sequentially
}

// Takes two (or three) elements: (condition, body1, body2)
// Conditional statement
Element *cond(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{args->elements[0]}));
    
}

// Takes two elements: (condition, body)
// Loop statement, calculate condition in loop, then execute body if true
Element *f_while(Context *context, List *args) {
    // [TODO: Evaluation]
}

// Takes one element
// and returns it as the result of function (only used in functions)
Element *f_return(Context *context, List *args) {
    // [TODO: Evaluation]
}

// Do not has any arguments,
// Just interupts a loop
Element *f_break(Context *context, List *args) {
    // [TODO: Evaluation]
}

// Takes two real or int elements,
// Returns their sum
Element *plus(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("plus", "Cannot compare arguments with different types");
    }

    if (a->getExecType() == typeInteger) {
        return new Integer(((Integer *) a)->value + ((Integer *) b)->value);
    } else if (a->getExecType() == typeReal) {
        return new Real(((Real *) a)->value + ((Real *) b)->value);
    } else {
        throw TypeMismatchException("plus", toString(a->getExecType()), "Integer or Real");
    }
}

// Takes two real or int elements,
// Returns their difference
Element *minus(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("minus", "Cannot compare arguments with different types");
    }

    if (a->getExecType() == typeInteger) {
        return new Integer(((Integer *) a)->value - ((Integer *) b)->value);
    } else if (a->getExecType() == typeReal) {
        return new Real(((Real *) a)->value - ((Real *) b)->value);
    } else {
        throw TypeMismatchException("minus", toString(a->getExecType()), "Integer or Real");
    }
}

// Takes two real or int elements,
// Returns their multiplication
Element *times(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("times", "Cannot compare arguments with different types");
    }

    if (a->getExecType() == typeInteger) {
        return new Integer(((Integer *) a)->value * ((Integer *) b)->value);
    } else if (a->getExecType() == typeReal) {
        return new Real(((Real *) a)->value * ((Real *) b)->value);
    } else {
        throw TypeMismatchException("times", toString(a->getExecType()), "Integer or Real");
    }
}

// Takes two real or int elements,
// Returns their division
Element *divide(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("divide", "Cannot compare arguments with different types");
    }

    if (a->getExecType() == typeInteger) {
        return new Integer(((Integer *) a)->value / ((Integer *) b)->value);
    } else if (a->getExecType() == typeReal) {
        return new Real(((Real *) a)->value / ((Real *) b)->value);
    } else {
        throw TypeMismatchException("divide", toString(a->getExecType()), "Integer or Real");
    }
}

// Takes list, returns its first element
Element *head(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));

    if (a->getExecType() != typeList) {
        throw TypeMismatchException("head", toString(a->getExecType()), toString(typeList));
    }
    return List::fromElement(a)->elements[0];
}

// Takes list, returns itself without first element
Element *tail(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));

    if (a->getExecType() != typeList) {
        throw TypeMismatchException("tail", toString(a->getExecType()), toString(typeList));
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
Element *cons(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{a}));

    if (b->getExecType() != typeList) {
        throw TypeMismatchException("cons", toString(b->getExecType()), toString(typeList));
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
Element *equal(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("equal", "Cannot compare arguments with different types");
    }

    switch (a->getExecType()) {
        case typeBoolean:
            return new Boolean(((Boolean *) a)->value == ((Boolean *) b)->value);
        case typeInteger:
            return new Boolean(((Integer *) a)->value == ((Integer *) b)->value);
        case typeReal:
            return new Boolean(((Real *) a)->value == ((Real *) b)->value);
        default:
            throw TypeMismatchException("equal", toString(a->getExecType()), "Literal");
    }
}

// Takes two elements of same type of int, real or bool,
// Returns true if elements are not equal, false otherwise
Element *nonequal(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("nonequal", "Cannot compare arguments with different types");
    }

    switch (a->getExecType()) {
        case typeBoolean:
            return new Boolean(((Boolean *) a)->value != ((Boolean *) b)->value);
        case typeInteger:
            return new Boolean(((Integer *) a)->value != ((Integer *) b)->value);
        case typeReal:
            return new Boolean(((Real *) a)->value != ((Real *) b)->value);
        default:
            throw TypeMismatchException("nonequal", toString(a->getExecType()), "Literal");
    }
}

// Takes two elements of same type of int, real or bool,
// Returns true if first element is less than second, false otherwise
Element *less(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("less", "Cannot compare arguments with different types");
    }

    switch (a->getExecType()) {
        case typeBoolean:
            return new Boolean(((Boolean *) a)->value < ((Boolean *) b)->value);
        case typeInteger:
            return new Boolean(((Integer *) a)->value < ((Integer *) b)->value);
        case typeReal:
            return new Boolean(((Real *) a)->value < ((Real *) b)->value);
        default:
            throw TypeMismatchException("less", toString(a->getExecType()),
                                            "Literal (number or bool)");
    }
}

// Takes two elements of same type of int, real or bool,
// Returns true if first element is less or equal to second, false otherwise
Element *lesseq(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("lesseq", "Cannot compare arguments with different types");
    }
    switch (a->getExecType()) {
        case typeBoolean:
            return new Boolean(((Boolean *) a)->value <= ((Boolean *) b)->value);
        case typeInteger:
            return new Boolean(((Integer *) a)->value <= ((Integer *) b)->value);
        case typeReal:
            return new Boolean(((Real *) a)->value <= ((Real *) b)->value);
        default:
            throw TypeMismatchException("lesseq", toString(a->getExecType()),
                                            "Literal (number or bool)");
    }
}

// Takes two elements of same type of int, real or bool,
// Returns true if first element is greater than second, false otherwise
Element *greater(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("greater", "Cannot compare arguments with different types");
    }

    switch (a->getExecType()) {
        case typeBoolean:
            return new Boolean(((Boolean *) a)->value > ((Boolean *) b)->value);
        case typeInteger:
            return new Boolean(((Integer *) a)->value > ((Integer *) b)->value);
        case typeReal:
            return new Boolean(((Real *) a)->value > ((Real *) b)->value);
        default:
            throw TypeMismatchException("greater", toString(a->getExecType()),
                                            "Literal (number or bool)");
    }
}

// Takes two elements of same type of int, real or bool,
// Returns true if first element is greater or equal to second, false otherwise
Element *greatereq(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != b->getExecType()) {
        throw CustomException("greatereq", "Cannot compare arguments with different types");
    }

    switch (a->getExecType()) {
        case typeBoolean:
            return new Boolean(((Boolean *) a)->value >= ((Boolean *) b)->value);
        case typeInteger:
            return new Boolean(((Integer *) a)->value >= ((Integer *) b)->value);
        case typeReal:
            return new Boolean(((Real *) a)->value >= ((Real *) b)->value);
        default:
            throw TypeMismatchException("greatereq", toString(a->getExecType()),
                                            "Literal (number or bool)");
    }
}

// Takes one argument, returns true if it is integer,
// Or false, otherwise
Element *isint(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    if (a->getExecType() == typeInteger)
        return new Boolean(true);
    else
        return new Boolean(false);
}

// Takes one argument, returns true if it is real,
// Or false, otherwise
Element *isreal(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    if (a->getExecType() == typeReal)
        return new Boolean(true);
    else
        return new Boolean(false);
}

// Takes one argument, returns true if it is boolean,
// Or false, otherwise
Element *isbool(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    if (a->getExecType() == typeBoolean)
        return new Boolean(true);
    else
        return new Boolean(false);
}

// Takes one argument, returns true if it is null,
// Or false, otherwise
Element *isnull(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    if (a->getExecType() == typeNil)
        return new Boolean(true);
    else
        return new Boolean(false);
}

// Takes one argument, returns true if it is an atom,
// Or false, otherwise
Element *isatom(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    if (a->getExecType() == typeAtom)
        return new Boolean(true);
    else
        return new Boolean(false);
}

// Takes one argument, returns true if it is a list,
// Or false, otherwise
Element *islist(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    if (a->getExecType() == typeList)
        return new Boolean(true);
    else
        return new Boolean(false);
}

// Takes two elements of type boolean,
// Returns result of logical and as boolean
Element *f_and(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != typeBoolean) {
        throw TypeMismatchException("and", toString(a->getExecType()), toString(typeBoolean));
    }

    if (b->getExecType() != typeBoolean) {
        throw TypeMismatchException("and", toString(b->getExecType()), toString(typeBoolean));
    }

    return new Boolean(((Boolean *) a)->value & ((Boolean *) b)->value);
}

// Takes two elements of type boolean,
// Returns result of logical or as boolean
Element *f_or(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != typeBoolean) {
        throw TypeMismatchException("or", toString(a->getExecType()), toString(typeBoolean));
    }

    if (b->getExecType() != typeBoolean) {
        throw TypeMismatchException("or", toString(b->getExecType()), toString(typeBoolean));
    }

    return new Boolean(((Boolean *) a)->value | ((Boolean *) b)->value);
}

// Takes two elements of type boolean,
// Returns result of logical xor as boolean
Element *f_xor(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));
    Element *b = eval(context, new List(new Elements{b}));

    if (a->getExecType() != typeBoolean) {
        throw TypeMismatchException("xor", toString(a->getExecType()), toString(typeBoolean));
    }

    if (b->getExecType() != typeBoolean) {
        throw TypeMismatchException("xor", toString(b->getExecType()), toString(typeBoolean));
    }

    return new Boolean(((Boolean *) a)->value & ((Boolean *) b)->value);
}

// Takes element of type boolean,
// Returns its logical negation as boolean
Element *f_not(Context *context, List *args) {
    Element *a = eval(context, new List(new Elements{a}));

    if (a->getExecType() != typeBoolean) {
        throw TypeMismatchException("not", toString(a->getExecType()), toString(typeBoolean));
    }

    return new Boolean(!((Boolean *) a)->value);
}

// Takes one element as argument,
// If it is list - return result of its evaluation
// Otherwise, just return
Element *eval(Context *context, List *args) {
    if (args->elements[0]->getExecType() != typeAtom) {
        throw TypeMismatchException("eval", toString(args->elements[0]->getExecType()),
                                    toString(typeAtom));
    }

    // [TODO: Evaluation]
}

Element *nil(Context *context, List *args) {
    return Nil::getNil();
}

Element *f_true(Context *context, List *args) {
    return new Boolean(true);
}

Element *f_false(Context *context, List *args) {
    return new Boolean(false);
}

std::map<std::string, Function *> getDefaultFunctions() {
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