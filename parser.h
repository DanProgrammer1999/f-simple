#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

static int tabPadding = 0;

class Element;
typedef std::vector<Element *> Elements;

class Element
{
public:
    virtual void print() {}
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

    Atom() {}
    Atom(std::string identifier) : identifier(identifier) {}

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

    Keyword(std::string identifier) : identifier(identifier) {}

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
};

class Integer : public Literal
{
public:
    int value;

    Integer() {}
    Integer(int value) : value(value) {}

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

    Real() {}
    Real(double value) : value(value) {}

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

    Boolean() {}
    Boolean(bool value) : value(value) {}

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
public:
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

    List() {}
    List(Elements elements) : elements(elements) {}

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
