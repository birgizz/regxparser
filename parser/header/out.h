#ifndef OUT_H
#define OUT_H

#include "op.h"
extern std::vector<std::string> captures;
extern std::string capture;

struct out: op {
    std::string rhs;
    std::string lhs;
    bool eval(it &begin, it &end) override{
        capture = rhs;
        if(!operands[0]->eval(begin,end)){

                 return false;
        }
        return true;
    
    }
    std::string id() override{
        return "OUT";
    }
};

#endif /* CAPTURE_H */
