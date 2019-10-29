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
}

%start Program
%token IDENTIFIER INTEGER REAL BOOLEAN KEYWORD

%%

Literal: INTEGER
	| BOOLEAN
	| REAL
	;

Atom: IDENTIFIER
	| KEYWORD
	| Literal
	;

SimpleList: '(' Element ')'
	| '(' ')' {$$ = Null}
	;

ElementList: Element
	| Element ElementList
	;

List: SimpleList
	| ElementList
	;

Element: Atom
	| List
	;

ElementSequence: Element
	| Element ElementSequence
	;

Program: ElementSequence;

%%
