//
// Created by danieldv99 on 29/11/2019.
//

#ifndef F_SIMPLE_SEMANTIC_H
#define F_SIMPLE_SEMANTIC_H

#include <map>

#include "parser.h"
#include "errors.h"

class Context;
typedef Element *(*FunctionPointer)(Context *, List *);

class Function;
class PredefinedFunction;
class CustomFunction;
class LambdaFunciton;

class DefaultFunctions;

#endif //F_SIMPLE_SEMANTIC_H
