#ifndef SUBSTITUTE_H
#define SUBSTITUTE_H

#include "op.h"
extern std::vector<std::string> captures;
extern bool tolow; 
struct or_expr : op {
    std::string rhs;
    std::string lhs;

    bool eval(it &begin, it &end) override{

        if (tolow) {
            auto input = std::string(begin, begin + rhs.size());
            std::transform(rhs.begin(), rhs.end(), rhs.begin(), ::tolower);
            std::transform(lhs.begin(), lhs.end(), lhs.begin(), ::tolower);
            if(input == rhs||input == lhs){
                captures.push_back(input);
                //std::cout << input<< std::endl;
                begin = begin + rhs.size() ;
                return true;
            }
        }else{
            auto input = std::string(begin, begin + rhs.size());
             if(input == rhs||input == lhs){
                captures.push_back(input);
                //std::cout << input<< std::endl;
                begin = begin + rhs.size() ;
                return true;
            }

        }
        return false;
    }
    std::string id() override{
        return "OR";
    }
};

#endif /* SUBSTITUTE_H */