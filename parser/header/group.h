#ifndef GROUP_H
#define GROUP_H

#include "op.h"

using it = std::string::iterator;
struct group: op {
    bool eval(it &begin, it &end)override{


        if(!operands[0]->eval(begin,end)){
                 return false;
        }
        return true;
        
        
       

    }
    std::string id() override{
        return "GROUP";
    }
};

#endif /* GROUP_H */
