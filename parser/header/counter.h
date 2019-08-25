#ifndef COUNTER_H
#define COUNTER_H

#include "op.h"
#include <string>



struct counter: op {
    std::string rhs;
    std::string lhs;
    bool eval(it &begin, it &end) override {

       for(auto e: operands){
           if(!e->eval(begin,end)){
                 return false;
           }
        }
        return true;

    }
    std::string id() override{
        return "COUNTER";
    }
};

#endif /* COUNTER_H */
