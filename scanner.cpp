// #include <ctype.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "parser.h"
#include "parser.tab.h"

#define yyterminate() return mapToCode(Token::Type::EndOfCode)

extern "C" int yylex();

class Token
{
public:
    enum class Type
    {
        EndOfCode,
        Identifier,
        Integer,
        Comment,
        LParent,
        RParent,
        Slash,
        WhatIsThatRyadovoyKucha,
        Keyword,
        Real,
        Boolean
    };

    Type m_type{};
    std::string m_lexema{};
    Token(Type type) : m_type{type} {}
    Token(Type type, std::string lexeme) : m_type{type}, m_lexema(lexeme) {}
    Token(Type type, char *beg, std::size_t len) : m_type{type}, m_lexema(beg, len) {}
    Token(Type type, char *beg, char *end) : m_type{type}, m_lexema(beg, std::distance(beg, end)) {}

    Type type() { return m_type; }
    void type(Type type) { m_type = type; }

    bool is(Type type) { return type == m_type; }
    bool is_not(Type type) { return type != m_type; }

    bool is_one_of(Type t1, Type t2) { return is(t1) || is(t2); }

    template <typename... Ts>
    bool is_one_of(Type t1, Type t2, Ts... ts)
    {
        return is(t1) || is_one_of(t2, ts...);
    }

    std::string lexeme() { return m_lexema; }
    void lexeme(std::string lexeme) { m_lexema = lexeme; }
};

class Lexer
{
public:
    char m_start;

    Lexer() {}
    Token next();

    Token identifier();
    Token number();
    Token number(std::string);
    Token slash_comment();
    Token string_literal();
    Token keyword(std::string);
    Token atom(Token::Type);

    char peek() { return m_start; }
    char get()
    {
        m_start = getchar();
        return m_start;
    }
    void reset() { ungetc(m_start, stdin); }
};

bool is_space(char c)
{
    switch (c)
    {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        return false;
    }
}

bool is_number(char c)
{
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    default:
        return false;
    }
}

bool is_identifier(char c)
{
    switch (c)
    {
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '_':
        return true;
    default:
        return false;
    }
}

Token Lexer::atom(Token::Type type)
{
    std::string val(1, m_start);
    return Token(type, val);
}

Token Lexer::next()
{
    std::string start;
    get();

    while (is_space(peek()))
        get();

    switch (peek())
    {
    case EOF:
        return atom(Token::Type::EndOfCode);
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        return identifier();
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return number();
    case '(':
        return atom(Token::Type::LParent);
    case ')':
        return atom(Token::Type::RParent);
    case '\'':
        return atom(Token::Type::Keyword);
    case '-':
        start += m_start;
        get();
        if (is_number(peek()))
        {
            return number(start);
        }
        else
        {
            reset();
            return atom(Token::Type::WhatIsThatRyadovoyKucha);
        }
    case '+':
        start += m_start;
        get();
        if (is_number(peek()))
        {
            return number(start);
        }
        else
        {
            reset();
            return atom(Token::Type::WhatIsThatRyadovoyKucha);
        }
    case '/':
    {
        Token isComment = slash_comment();
        if (isComment.is_not(Token::Type::Slash))
        {
            return isComment;
        }
    }
    default:
        return atom(Token::Type::WhatIsThatRyadovoyKucha);
    }
}

Token Lexer::identifier()
{
    std::string start;
    start += peek();
    while (is_identifier(get()))
    {
        start += peek();
    }
    reset();
    return keyword(start);
}

Token Lexer::keyword(std::string lexeme)
{
    if (
        lexeme == "true" ||
        lexeme == "false")
        return Token(Token::Type::Boolean, lexeme);

    if (
        lexeme == "setq" ||
        lexeme == "func" ||
        lexeme == "lambda" ||
        lexeme == "prog" ||
        lexeme == "cond" ||
        lexeme == "while" ||
        lexeme == "return" ||
        lexeme == "break")
    {
        return Token(Token::Type::Keyword, lexeme);
    }
    else
    {
        return Token(Token::Type::Identifier, lexeme);
    }
}

Token Lexer::number()
{
    std::string start;
    start += peek();
    while (is_number(get()))
    {
        start += peek();
    }

    if (peek() == '.')
    {
        start += peek();
        if (is_number(get()))
        {
            while (is_number(get()))
            {
                start += peek();
            }

            return Token(Token::Type::Real, start);
        }
        else
        {
            reset();
        }
    }
    reset();
    return Token(Token::Type::Integer, start);
}

Token Lexer::number(std::string start)
{
    start += peek();
    while (is_number(get()))
    {
        start += peek();
    }

    if (peek() == '.')
    {
        start += peek();
        if (is_number(get()))
        {
            while (is_number(get()))
            {
                start += peek();
            }
            reset();
            return Token(Token::Type::Real, start);
        }
        else
        {
            reset();
        }
    }
    reset();
    return Token(Token::Type::Integer, start);
}

Token Lexer::slash_comment()
{
    std::string start;
    start += peek();
    get();
    if (peek() == '/')
    {
        start += peek();
        get();
        start = m_start;
        while (peek() != '\0')
        {
            if (get() == '\n')
            {
                return Token(Token::Type::Comment, start);
            }
        }
        return atom(Token::Type::WhatIsThatRyadovoyKucha);
    }
    reset();
    return atom(Token::Type::Slash);
}

std::ostream &operator<<(std::ostream &os, const Token::Type &type)
{
    static std::string names[]{
        "EndOfCode",
        "Identifier",
        "Integer",
        "Comment",
        "LParent",
        "RParent",
        "Slash",
        "WhatIsThatRyadovoyKucha",
        "Keyword",
        "Real",
        "Boolean"};
    return os << names[static_cast<int>(type)];
}

int mapToCode(Token::Type type)
{
    static int tokens[11] = {END,
                             IDENTIFIER,
                             INTEGER,
                             1,
                             LPARENT,
                             RPARENT,
                             2,
                             3,
                             KEYWORD,
                             REAL,
                             BOOLEAN};
    return tokens[static_cast<int>(type)];
}

int yylex()
{
    Lexer lexer;
    auto token = lexer.next();

    // std::cout << token.type() << " " << token.lexeme() << std::endl;

    if (token.type() == Token::Type::EndOfCode)
    {
        clearerr(stdin);
        return -1;
    }

    if (token.type() == Token::Type::Identifier || token.type() == Token::Type::Keyword)
    {
        yylval.string = new std::string(token.lexeme());
    }
    else
    {
        yylval.token = mapToCode(token.type());
    }

    return mapToCode(token.type());
}