#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

static int tabPadding = 0;

enum ExecutionType
{
    typeElement,
    typeAtom,
    typeKeyword,
    typeLiteral,
    typeInteger,
    typeReal,
    typeBoolean,
    typeNil,
    typeList,
    typePredefinedList
};

const std::string toString(ExecutionType type) {
    switch (type) {
        typeElement: return "Element";
        typeAtom: return "Atom";
        typeKeyword: return "Keyword";
        typeLiteral: return "Literal";
        typeInteger: return "Integer";
        typeReal: return "Real";
        typeBoolean: return "Boolean";
        typeNil: return "Nil";
        typeList: return "List";
        typePredefinedList: return "List";
        default:
            return "UNKNOWN TYPE";
    }
}

class Element;
typedef std::vector<Element *> Elements;

class Element
{
    // store execution type as enum
protected:
    ExecutionType execType;

public:
    virtual void print() {}
    ExecutionType getExecType()
    {
        return execType;
    }
};

class Program
{
public:
    Elements elements;

    Program() {}
    Program(Elements elements) : elements(elements) {}

    void print()
    {
        std::cout << "Printing Program items with size " << elements.size() << std::endl;
        tabPadding++;
        for (int i = 0; i < elements.size(); ++i)
        {
            elements.at(i)->print();
        }
        tabPadding--;
    }
};

class Atom : public Element
{
public:
    std::string identifier;

    // in constructors add its type
    Atom()
    {
        execType = typeAtom;
    }
    Atom(std::string identifier) : identifier(identifier)
    {
        execType = typeAtom;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6) << "|---"
                  << " ATOM->" << identifier << std::endl;
        tabPadding--;
    }
};

class Keyword : public Atom
{
public:
    std::string identifier;

    Keyword(std::string identifier) : identifier(identifier)
    {
        execType = typeKeyword;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6);
        std::cout << "|---"
                  << " KEYWORD->" << identifier << std::endl;
        tabPadding--;
    }
};

class Literal : public Element
{
public:
    Literal()
    {
        execType = typeLiteral;
    }
};

class Integer : public Literal
{
public:
    int value;

    Integer()
    {
        execType = typeInteger;
    }
    Integer(int value) : value(value)
    {
        execType = typeInteger;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6) << "|---"
                  << " INTEGER->" << value << std::endl;
        tabPadding--;
    }
};

class Real : public Literal
{
public:
    double value;

    Real()
    {
        execType = typeReal;
    }
    Real(double value) : value(value)
    {
        execType = typeReal;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6) << "|---"
                  << " REAL->" << value << std::endl;
        tabPadding--;
    }
};

class Boolean : public Literal
{
public:
    bool value;

    Boolean(bool value) : value(value)
    {
        execType = typeBoolean;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6) << "|---"
                  << " BOOL->" << value << std::endl;
        tabPadding--;
    }
};

class Nil : public Literal
{
private:
    static Nil* object;
    Nil()
    {
        execType = typeNil;
    }

public:
    static Nil* getNil(){
        if(object == nullptr){
            object = new Nil();
        }

        return object;
    }
    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6);
        std::cout << "|---"
                  << " NULL" << std::endl;
        tabPadding--;
    }
};

class List : public Element
{
public:
    Elements elements;

    List()
    {
        execType = typeList;
    }
    List(Elements elements) : elements(elements)
    {
        execType = typeList;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6);
        std::cout << "|---"
                  << " Printing list items with size " << elements.size() << std::endl;
        for (int i = 0; i < elements.size(); ++i)
        {
            elements.at(i)->print();
        }
        tabPadding--;
    }
};

class PredefinedList : public List
{
public:
    PredefinedList(Keyword *keyword, Elements elements)
    {
        execType = typePredefinedList;
        elements.push_back(keyword);
        this->elements.insert(this->elements.end(), elements.begin(), elements.end());
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6);
        std::cout << "|---"
                  << " Printing predefined list items with size " << elements.size() << std::endl;
        for (int i = 0; i < elements.size(); ++i)
        {
            elements.at(i)->print();
        }
        tabPadding--;
    }
};
