#ifndef SINGLE_EXPR_H
#define SINGLE_EXPR_H

#include "op.h"


struct single_expr: op {
    bool eval(it &begin, it &end) override{

        if(!operands[0]->eval(begin,end)){
                 return false;
        }
        return true;
    }
    std::string id() override{
        return "SINGLE_EXPR";
    }
};

#endif /* BASIC_RE_H */
