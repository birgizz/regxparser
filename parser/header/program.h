#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include "op.h"
#include <string>

extern std::vector<std::string> captures;
extern std::string capture;

struct program : op {
    std::string _id;

    bool eval(it &begin, it &end) override{

        auto original_begin = begin;
        auto original_end = begin;

        while(begin != end){
            auto current_begin = begin;
            if(operands[0]->eval(current_begin, end)){
                if(operands[0]->id() == "OUT"){
                    std::cout << captures[std::stoi(capture)] << std::endl;

                } else if(operands[0]->id() == "EXPR")
                {
                    std::cout << std::string(begin,current_begin) << std::endl;

                }
                return true;
            }
            begin++;
        }
        std::cout << "false" << std::endl;

        return false;
    }
    std::string id() override{
        return "PROGRAM";
    }
};

#endif /* PROGRAM_H */
 