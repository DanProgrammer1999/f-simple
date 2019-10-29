#ifndef F_SIMPLE_PARSER_H
#define F_SIMPLE_PARSER_H

#include <list>

struct Literal {
    int *integer_value;
    bool *boolean_value;
    double *real_value;

    explicit Literal(int *integer_value = nullptr, bool *boolean_value = nullptr, double *real_value = nullptr) :
            integer_value(integer_value), boolean_value(boolean_value), real_value(real_value) {};
};

struct Atom {
    char *identifier;
    bool is_keyword;
    Literal *literal;

    Atom(char *identifier, bool is_keyword, Literal *literal = nullptr) :
            identifier(identifier), is_keyword(is_keyword), literal(literal) {};
};

struct Element;
struct List {
    std::list<Element *> list;

    explicit List(Element *element = nullptr) {
        list.push_back(element);
    }

    void addElement(Element *element) {
        list.push_back(element);
    }
};

const List null = List();

struct Element {
    Atom *atom;
    List *list;

    explicit Element(Atom *atom = nullptr, List *list = nullptr):
            atom(atom), list(list){};
};

struct ElementSequence {
    std::list <Element *> elementList;

    explicit ElementSequence(Element* element){
        elementList.push_back(element);
    }
};

#endif //F_SIMPLE_PARSER_H
