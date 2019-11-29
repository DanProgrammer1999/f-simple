
#ifndef F_SIMPLE_PREDEFINED_FUNCTIONS_H
#define F_SIMPLE_PREDEFINED_FUNCTIONS_H

#include "parser.h"
#include "errors.h"
#include "function.h"
#include "context.h"

Element *quote(Context *context, List *args);
Element *setq(Context *context, List *args);
Element *func(Context *context, List *args);
Element *lambda(Context *context, List *args);
Element *prog(Context *context, List *args);
Element *cond(Context *context, List *args);
Element *f_while(Context *context, List *args);
Element *f_return(Context *context, List *args);
Element *f_break(Context *context, List *args);
Element *plus(Context *context, List *args);
Element *minus(Context *context, List *args);
Element *times(Context *context, List *args);
Element *divide(Context *context, List *args);
Element *head(Context *context, List *args);
Element *tail(Context *context, List *args);
Element *cons(Context *context, List *args);
Element *equal(Context *context, List *args);
Element *nonequal(Context *context, List *args);
Element *less(Context *context, List *args);
Element *lesseq(Context *context, List *args);
Element *greater(Context *context, List *args);
Element *greatereq(Context *context, List *args);
Element *isint(Context *context, List *args);
Element *isreal(Context *context, List *args);
Element *isbool(Context *context, List *args);
Element *isnull(Context *context, List *args);
Element *isatom(Context *context, List *args);
Element *islist(Context *context, List *args);
Element *f_and(Context *context, List *args);
Element *f_or(Context *context, List *args);
Element *f_xor(Context *context, List *args);
Element *f_not(Context *context, List *args);
Element *eval(Context *context, List *args);
Element *nil(Context *context, List *args);
Element *f_true(Context *context, List *args);
Element *f_false(Context *context, List *args);

#endif //F_SIMPLE_PREDEFINED_FUNCTIONS_H
