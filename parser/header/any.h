#ifndef ANY_H
#define ANY_H
#include "op.h"

struct any: op {
    bool eval(it &begin, it &end) override {
            return true;
   
    }
    std::string id() override{
        return ".";
    }
};

#endif /* ANY_H */
