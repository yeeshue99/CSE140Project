#ifndef RTYPE_H
#define RTYPE_H

#include "Instruction.h"
#include <string>

class RType: public Instruction {
    private:
        int op;
        std::string label;
        int rs;
        int rt;
        int rd;
        int shamt;
        int func;

    public:
        RType(int op, std::string label, int func);
        RType(int op, std::string label, int rs, int rt, int rd, int shamt, int func);
        void print();
};

#endif