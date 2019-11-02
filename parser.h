#ifndef F_SIMPLE_PARSER_H
#define F_SIMPLE_PARSER_H

#include <list>

struct Literal {
    int *integer_value;
    bool *boolean_value;
    double *real_value;

    Literal(int *integer_value, bool *boolean_value, double *real_value) :
            integer_value(integer_value), boolean_value(boolean_value), real_value(real_value) {};
};

struct Atom {
    char *identifier{};
    bool is_keyword = false;
    Literal *literal{};

    Atom(char *identifier, bool is_keyword) :
            identifier(identifier), is_keyword(is_keyword) {};

    explicit Atom(Literal *literal):
        literal(literal){};
};

struct Element;

struct List {
    std::list<Element *> list;
    bool is_null = false;

    explicit List(Element *element) {
        if (element != nullptr) {
            list.push_back(element);
        } else {
            is_null = true;
        }
    }

    void addElement(Element *element) {
        list.push_back(element);
    }
};

const List null = List(nullptr);

struct Element {
    Atom *atom;
    List *list;

    explicit Element(Atom *atom, List *list) :
            atom(atom), list(list) {};
};

#endif //F_SIMPLE_PARSER_H
