#ifndef ITYPE_H
#define ITYPE_H

#include "Instruction.h"
#include <string>

class IType: public Instruction {
    private:
        int op;
        std::string label;
        std::string rs;
        std::string rt;
        int immediate;
        std::map<std::string, std::string> registerMap;

    public:
        IType(int op, std::string label);
        IType(int op, std::string label, std::string rs, std::string rt, int immediate, std::map<std::string, std::string> registerMap);
        void print();
};

#endif