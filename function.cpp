#include "function.h"

Element* CustomFunction::eval(Context *currContext, List *args) {
        if (args->elements.size() != this->args_number) {
            throw new ArgNumberMismatchException(this->name, args->elements.size(), this->args_number);
        }
        auto local_context = currContext->copy();
        // Context MUST NOT be used here, need it because of override
        // arguments are already eval'd
        for (int i = 0; i < this->args->size(); i++) {
            std::vector<std::string> *temp1 = new std::vector<std::string>();
            std::vector<Element *> *temp2 = new std::vector<Element *>{args->elements[i]};
            auto arg = new CustomFunction((*(this->args))[i], temp1,
                                          temp2, local_context);
            local_context->set((*(this->args))[i], arg);
        }

        auto res = local_context->get("eval")->eval(local_context, new List(this->body));
        return res;
    }