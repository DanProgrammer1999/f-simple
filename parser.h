#include <list>
#include <vector>
#include <string>

class Element;
typedef std::vector<Element*> Elements;

class Program {
public:
    Elements elements;

    Program() {}
    Program(Elements elements) : elements(elements) {}
};

class Element {};

class Atom : public Element {
public:
    std::string identifier;

    Atom() {}
    Atom(std::string identifier) : identifier(identifier) {}
};

class Keyword : public Atom {};

class Literal : public Element {};

class Integer : public Literal {
    int value;

    Integer() {}
    Integer(int value) : value(value) {}
};

class Real : public Literal {
    double value;

    Real() {}
    Real(double value) : value(value) {}
};

class Boolean : public Literal {
    bool value;

    Boolean() {}
    Boolean(bool value) : value(value) {}
};

class Null : public Literal {};

class List : public Element {
public:
    Elements elements;

    List() {}
    List(Elements elements) : elements(elements) {}
};

class PredefinedList : public List {
    PredefinedList(Keyword* keyword) {
        elements.push_back(keyword);
    }
};



