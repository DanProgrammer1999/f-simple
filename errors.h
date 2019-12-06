#ifndef F_SIMPLE_ERRORS_H
#define F_SIMPLE_ERRORS_H

 #include <bits/exception.h>
#include <string>
#include <sstream>
#include <exception>

class SemanticException : public std::exception {
protected:
    std::string message;
public:
    SemanticException(std::string message) : message(message) {};

    const char *what() const throw() override {
        return this->message.c_str();
    }

    const std::string toString() {
        return this->message;
    }
};

class CustomException : SemanticException {
public:
    CustomException(std::string function_name, std::string custom_message) :
            SemanticException(build_message(function_name, custom_message)) {};

    static std::string build_message(std::string function_name, std::string custom_message) {
        std::stringstream message_stream;
        message_stream << "Exception in function " << function_name << "\n";
        message_stream << custom_message << std::endl;

        return message_stream.str();
    }
};

class ArgNumberMismatchException : public SemanticException {

public:
    ArgNumberMismatchException(std::string function_name, int received, int required) :
            SemanticException(build_message(function_name, received, required)) {};

    static std::string build_message(std::string function_name, int received, int required) {
        std::stringstream message_stream;
        message_stream << "Incorrect number of arguments received in function " << function_name << "\n";
        message_stream << "Received " << received << (received == 1 ? " argument" : " arguments");
        message_stream << ", but " << required << (required == 1 ? " was" : " were") << " expected" << std::endl;

        return message_stream.str();
    }
};

class TypeMismatchException : public SemanticException {
public:
    TypeMismatchException(std::string function_name, std::string received, std::string required) :
            SemanticException(build_message(function_name, received, required)) {};

    static std::string build_message(std::string function_name, std::string received, std::string required) {
        std::stringstream message_stream;
        message_stream << "Incorrect type of argument received in function " << function_name << "\n";
        message_stream << "Received type " << received << ", but type " << required << " is expected" << std::endl;

        return message_stream.str();
    }
};

class NoSuchFunctionException : SemanticException {
public:
    NoSuchFunctionException(std::string function_name, std::string name_received) :
    SemanticException(build_message(function_name, name_received)) {};

    static std::string build_message(std::string function_name, std::string name_received) {
        std::stringstream message_stream;
        message_stream << "Atom \"" << name_received << "\" specified in function " << function_name;
        message_stream << "could not be resolved." << std::endl;

        return message_stream.str();
    }
};

#endif //F_SIMPLE_ERRORS_H
