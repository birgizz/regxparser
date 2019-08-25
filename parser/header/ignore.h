#ifndef IGNORE_H
#define IGNORE_H
#include <cstring>
#include "op.h"

using it = std::string::iterator;
struct ignore: op {
    std::string _id;
    bool eval(it &begin, it &end) override {
       for(auto e: operands){
           if(!e->eval(begin,end)){
                 return false;
           }
        }
        return true;
    }
    std::string id() override{
        return "IGNORE";
    }
};

#endif /* LOWERCASE_H */
