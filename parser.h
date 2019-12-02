#ifndef F_SIMPLE_PARSER_H
#define F_SIMPLE_PARSER_H

#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
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
    typePredefinedList,
    typeFunction,
};

static std::string toString(ExecutionType type) {
    switch (type) {
        case typeElement: return "Element";
        case typeAtom: return "Atom";
        case typeKeyword: return "Keyword";
        case typeLiteral: return "Literal";
        case typeInteger: return "Integer";
        case typeReal: return "Real";
        case typeBoolean: return "Boolean";
        case typeNil: return "Nil";
        case typeList: return "List";
        case typePredefinedList: return "List";
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
    virtual std::string toString(){ return "<Something else>";};
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

    std::string toString() {
        std::stringstream output;
        output << "<Program>" << std::endl;
        for(auto elem = elements.begin(); elem != elements.end(); ++elem){
            output << "\t" << (*elem)->toString() << std::endl;
        }
        return output.str();
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

    std::string toString() override {
        return std::string("<Atom> ") + identifier;
    }

    static Atom *fromElement(Element *element){
        if(element->getExecType() != typeAtom){
            return nullptr;
        }

        return static_cast<Atom *>(element);
    }
};

class Keyword : public Atom
{
public:

    Keyword(std::string identifier) : Atom(identifier)
    {
        execType = typeAtom;
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

    static Literal *fromElement(Element *element){
        if(element->getExecType() != typeLiteral){
            return nullptr;
        }

        return static_cast<Literal *>(element);
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

    std::string toString() override{
        return std::string("<Integer> ") + std::to_string(value);
    }

    static Integer *fromElement(Element *element){
        if(element->getExecType() != typeInteger){
            return nullptr;
        }

        return static_cast<Integer *>(element);
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

    std::string toString() override{
        return std::string("<Real> ") + std::to_string(value);
    }

    static Real *fromElement(Element *element){
        if(element->getExecType() != typeReal){
            return nullptr;
        }

        return static_cast<Real *>(element);
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

    std::string toString() override{
        return std::string("<Boolean> ") + std::to_string(value);
    }

    static Boolean *fromElement(Element *element){
        if(element->getExecType() != typeBoolean){
            return nullptr;
        }

        return static_cast<Boolean *>(element);
    }
};

class Nil : public Literal
{
public:
    Nil() {
        execType = typeNil;
    }

    void print() override
    {
        tabPadding++;
        std::cout << std::setw(tabPadding * 6);
        std::cout << "|---"
                  << " NULL" << std::endl;
        tabPadding--;
    }

    std::string toString() override{
        return std::string("<Nil> ");
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

    List(Element *element)
    {
        elements = *(new Elements{element});
        execType = typeList;
    }

    List(Elements *elements){
        this->elements = *elements;
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

    std::string toString() override{
        std::stringstream message_stream;
        message_stream << "<List> (";
        for(auto elem = elements.begin(); elem != elements.end(); ++elem){
            message_stream << (*elem)->toString() << "; ";
        }

        message_stream << ")";

        return message_stream.str();
    }

    static List *fromElement(Element *element){
        if(element->getExecType() != typeList){
            return nullptr;
        }

        return static_cast<List *>(element);
    }
};

class PredefinedList : public List
{
public:
    PredefinedList(Keyword *keyword, Elements elements)
    {
        execType = typeList;
        this->elements.push_back(keyword);
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

Integer *toInteger(Element *element);
Real *toReal(Element *element);
Boolean *toBool(Element *element);

#endif //F_SIMPLE_PARSER_H