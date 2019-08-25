#ifndef CHAR_EXPR_H
#define CHAR_EXPR_H

#include "op.h"
extern it begin_of_match;
struct char_expr : op {
    std::string _id;
    std::string ss;
    bool eval(it &begin, it &end) override{
        if (_id == "*") {
            begin_of_match = begin;
            begin  = end;
            return true;
        }else
        {
            while(*begin == _id[0]){
                begin++;
            }
            return true;
        }
        
        
         
    }
    std::string id() override{
        return _id;
    }
};

#endif /* char_expr */