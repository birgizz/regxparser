#ifndef OP_H
#define OP_H

#include <string>
#include <vector>
#include <iostream>
using it = std::string::iterator;


struct op {
    virtual bool eval(it &begin, it &end) = 0;
    virtual std::string id() = 0;
    std::vector<op*> operands;
};

#endif /* OP_H */

