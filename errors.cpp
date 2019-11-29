#include "errors.h"

class SemanticException : public std::exception{
protected:
    std::string message;
    SemanticException(std::string message): message(message){};
};

class ArgNumberMismatchException : public SemanticException{

public:
    ArgNumberMismatchException(std::string function_name, int received, int required) :
            message(build_message(function_name, received, required)) {};

    const char *what() const throw() override {
        return this->message.c_str();
    }

    static std::string build_message(std::string function_name, int received, int required) {
        std::stringstream message_stream;
        message_stream << "Incorrect number of arguments received in function " << function_name << "\n";
        message_stream << "Received " << received << (received == 1 ? " argument" : " arguments");
        message_stream << ", but " << required << (required == 1 ? " was" : " were") << " expected" << std::endl;

        return message_stream.str();
    }
};

class TypeMismatchException : public std::exception {
private:
    std::string message;
public:
    TypeMismatchException(std::string function_name, std::string received, std::string required) :
            message(build_message(function_name, received, required)) {};

    const char *what() const throw() override {
        return this->message.c_str();
    }

    static std::string build_message(std::string function_name, std::string received, std::string required) {
        std::stringstream message_stream;
        message_stream << "Incorrect number of arguments received in function " << function_name << "\n";
        message_stream << "Received type " << received << ", but type " << required << " is expected" << std::endl;

        return message_stream.str();
    }
};