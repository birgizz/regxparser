#ifndef CONCAT_h
#define CONCAT_h
#include <algorithm>
#include "op.h"
using it = std::string::iterator;

struct concat_expr : op {
    bool eval(it &begin, it &end) override{
        
        for(auto e: operands){
           if(!e->eval(begin,end)){
                 return false;
           }
        }
        return true;

    }
    std::string id() override {
        return "CONCAT";
    }
};

#endif /* CONCAT_h */
