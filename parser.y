%{
	int yylex(void);
        int yyparse();
        int yyerror(const char *msg);
%}

%union{
	struct ElementSequence *program;
	struct Element *element;
	struct Atom *atom;
	struct List *list;
	struct Literal *literal;
	const List *null;
}

%start Program
%token IDENTIFIER INTEGER REAL BOOLEAN KEYWORD

%%

Literal: INTEGER	{$$ = new Literal($1, nullptr, nullptr);}
	| BOOLEAN	{$$ = new Literal(nullptr, $1, nullptr);}
	| REAL     	{$$ = new Literal(nullptr, nullptr, $1);}
	;

Atom: IDENTIFIER	{$$ = new Atom($1, false);}
	| KEYWORD	{$$ = new Atom($1, true);}
	| Literal	{$$ = new Atom($1);}
	;

SimpleList: '(' Element ')'	{$$ = new List($1);}
	| '(' ')'		{$$ = null;}
	;

ElementList: Element		{$$ = new List($1);}
	| Element ElementList   {$1->addElement($2); $$ = $1;}
	;

List: SimpleList	{$$ = $1;}
	| ElementList	{$$ = $1;}
	;

Element: Atom	{$$ = new Element($1, nullptr);}
	| List	{$$ = new Element(nullptr, $1);}
	;

ElementSequence: Element		{$$ = new List($1);}
	| Element ElementSequence	{$1->addElement($2); $$ = $1;}
	;

Program: ElementSequence {$$ = $1;};

%%
