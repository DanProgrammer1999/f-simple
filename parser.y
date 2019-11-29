%{
	#include "parser.h"
	#include <iostream>
	#include <string>

	Program* root;
	bool no_err = true;

	extern "C" int yylex();
	extern "C" int yyparse();
	void yyerror(const char* s) { printf("ERROR: %sn", s); no_err = false; }
%}

%union {
	int token;
	std::string *string;

	Program* program;
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
	: Elements END {root = new Program(*$1); root->print();}
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
	| REAL		{$$ = new Real($1);}
	| BOOLEAN	{$$ = new Boolean($1);}
	| NIL		{$$ = new Nil();}
	;

List
	: LPARENT	           RPARENT {$$ = new List(); $$->print();}
	| LPARENT      	  Elements RPARENT {$$ = new List(*$2); $$->print();}
	| LPARENT KEYWORD Elements RPARENT {Keyword *keyword = new Keyword(*$2); $$ = new PredefinedList(keyword, *$3); $$->print();}
	;

%%

int main(int argc, char **argv)
{
	yyparse();
	if (!no_err) {
		return -1;
	}

	std::cout << root << std::endl;
    
    return 0;
}