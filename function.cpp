#include "function.h"

 CustomFunction::CustomFunction(std::string name, std::vector<std::string> *args, List *body,Context *localContext) : 
                 Function(name, args), localContext(localContext) {

    this->body = body;
    this->localContext->set(this->name, this);
};

Element* CustomFunction::eval(Context *currContext, List *args) {
        if (args->elements.size() != this->args_number) {
            std::cout << "Custom function has incorrect number of args: " << args->toString() << "\n";
            throw ArgNumberMismatchException(this->name, args->elements.size(), this->args_number);
        }
        auto local_context = currContext->copy();
        // Context MUST NOT be used here, need it because of override
        // arguments are already eval'd

        for (int i = 0; i < this->args->size(); i++) {
            auto empty_args = new std::vector<std::string>();
            auto value = new List(args->elements[i]);
            auto arg = new CustomFunction((*(this->args))[i], empty_args,
                                          value, local_context);
            local_context->set((*(this->args))[i], arg);
        }
        auto res = local_context->get("eval")->eval(local_context, this->body);
        return res;
    }