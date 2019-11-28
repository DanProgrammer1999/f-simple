# Project F

## Compiler for the functional Toy language

Compiler Construction,
Innopolis University

# Evaluation
Program is a sequence of elements. Each element is evaluated as soon as it is parsed.

## How to evaluate element
- If it is a literal, just return its value
- If it is an atom, try to lookup its value in Context, otherwise throw error (?)
- If it is a list, evaluate it and return the result

## How to evaluate list
- If first value is an atom (identifier, e.g. `minus` or `my_func`, treat it as a function call:
    - Check number of arguments (separated by whitespaces, not a single list)
    - Evaluate each argument (recursively, each argument is an element)
    - Evaluate function with the arguments (should be evaluated to literals)
    - Return result
- Otherwise (if first value is a literal or list), treat it as just a list (literal) and return it as it is

## Note on my current idea of storing functions (any suggestions?) (Delete later this part)

Create objects of class `Function` (for default functions) and pass the handler 
(reference to function) as an argument. Dictionary should now store `Function *` as a value.
Also, now we can move the number of arguments check to the class `Function`, so we don't need it
in the handlers as well.
