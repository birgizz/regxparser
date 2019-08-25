#ifndef DIGIT_H
#define DIGIT_H

#include "op.h"


struct digit : op {
    std::string _id;
    std::string digits = "0123456789";
    bool eval(it &begin, it &end) override{
        begin = begin + std::stoi(_id);
        return true;
    }
    std::string id() override{
        return this->_id;
    }
};

#endif /* DIGIT_H */