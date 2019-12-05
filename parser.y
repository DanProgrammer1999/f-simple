%{
	#include "parser.h"
	#include "context.h"
	#include "predefined_functions.h"
	#include<stdio.h>
	#include<string.h>
	#include <iostream>
	#include <string>

	List* root;
	Context* global = new Context();
	bool no_err = true;

	extern "C" int yylex();
	extern "C" int yyparse();
	void yyerror(const char* s) { printf("ERROR: %s\n", s); no_err = false; }
%}

%union {
	int token;
	std::string *string;

	double real;
	bool boolean;
	int integer;

	List* program;
	Element* element;
	Literal* literal;
	Elements* elements;
	Atom* atom;
	List* list;
}

%token <string> 	IDENTIFIER KEYWORD

%token <token> 		INTEGER REAL BOOLEAN NIL
%token END 		0

%token <token> 		LPARENT
%token <token> 		RPARENT

%type <program> 	Program
%type <element> 	Element
%type <elements> 	Elements
%type <literal> 	Literal
%type <atom> 		Atom
%type <list> 		List

%start Program

%%

Program
	: Elements END {root = new List($1);}
	;

Elements
	: Element	        {$$ = new Elements(); $$->push_back($1);}
	| Elements Element	{$1->push_back($2);}
	;

Element
	: Atom		{$$ = $1;}
	| Literal	{$$ = $1;}
	| List		{$$ = $1;}
	;

Atom
	: IDENTIFIER {$$ = new Atom(*$1);}
	;

Literal
	: INTEGER	{$$ = new Integer($1);}
	| REAL		{$$ = new Real(yylval.real);}
	| BOOLEAN	{$$ = new Boolean(yylval.boolean);}
	| NIL		{$$ = new Nil();}
	;

List
	: LPARENT	           RPARENT {$$ = new List();}
	| LPARENT      	  Elements RPARENT {$$ = new List($2);}
	| LPARENT KEYWORD Elements RPARENT {Keyword *keyword = new Keyword(*$2); $$ = new PredefinedList(keyword, *$3);}
	| KEYWORD Elements {Keyword *keyword = new Keyword("quote"); $$ = new PredefinedList(keyword, *$2);}
	;

%%

int main(int argc, char **argv)
{
	bool interactive = false;
	Context *context = new Context();
	if (argc > 1 && strcmp(argv[1], "-i") == 0) {
		interactive = true;
	}
	do {
		try {
			yyparse();
			if (no_err) {
				std::cout << root << std::endl;
				Element* res = prog(global, new List(root)); 
				std::cout << "\nProgram returned " << res->toString() << std::endl;
			} else {
				std::cout << "SYNTAX ERROR HANDLED\n";
			}
			// ungetc(EOF, stdin);
			clearerr(stdin);
		} catch (const std::exception& e) {
			std::cout << "ERROR HANDLED: ";
			std::cout << e.what() << std::endl;
			clearerr(stdin);
		}
	} while (interactive);
    
    return 0;
}
