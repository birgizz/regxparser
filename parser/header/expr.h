#ifndef EXPR_H
#define EXPR_H
#include "op.h"
struct expr: op {
    bool eval(it &begin, it &end) override{
        for(auto e: operands){
           if(!e->eval(begin,end)){
                 return false;
           }
        }
        return true;
    }
    std::string id() override{
        return "EXPR";
    }
};
#endif /* expr */
