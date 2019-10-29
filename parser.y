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

Program: ElementSequence;

ElementSequence: Element
	| Element ';' ElementSequence
	;

Element: Atom
	| List
	;

Atom: IDENTIFIER
	| KEYWORD
	| Literal
	;

List: SimpleList
	| ElementList
	;

SimpleList: '(' Element ')'
	| '(' ')' {$$ = Null}
	;

ElementList: Element
	| Element ElementList
	;

Literal: INTEGER
	| BOOLEAN
	| REAL
	;

%%
