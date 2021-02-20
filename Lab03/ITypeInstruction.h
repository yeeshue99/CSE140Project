#ifndef ITYPE_H
#define ITYPE_H

#include "Instruction.h"
#include <string>

class IType: public Instruction {
    private:
        int op;
        std::string label;
        int rs;
        int rt;
        int immediate;

    public:
        IType(int op, std::string label);
        IType(int op, std::string label, int rs, int rt, int immediate);
        void print();
};

#endif