#ifndef STRING_H
#define STRING_H

#include "op.h"
#include <string>
extern std::vector<std::string> captures;
extern it begin_of_match;
struct string : op {
    std::string _id;
    bool eval(it &begin, it &end) override {
        auto input = std::string(begin, begin + _id.size());
            if(input == _id){
                captures.push_back(input);
                begin = begin + _id.size();
                return true;
            }
            auto a =end; 
            if (begin == end) {
                while(begin == end){
                input = std::string(a -_id.size(), a);
                if(input == _id){
                captures.push_back(std::string(begin_of_match, a));
                captures.push_back(input);
                begin = a;
                return true;
                }
                a--;
            }

            }
            
            
           
            return false;
    }
    std::string id() override{
        return _id;
    }
    int size() {
        return _id.size();
    }
};
#endif /* CHARACTER_H */