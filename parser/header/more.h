#ifndef MORE_H
#define MORE_H

#include "more.h"
struct more : op {
    std::string rhs;
    std::string lhs;
    bool eval(it &begin, it &end) override{
        for(auto e: operands){
           if(!e->eval(begin,end)){
                 return false;
           }
        }
        return true;
    
        
    }
    std::string id() override{
        return "MORE";
    }
};

#endif /* STAR_H */