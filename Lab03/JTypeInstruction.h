#ifndef JTYPE_H
#define JTYPE_H

#include "Instruction.h"
#include <string>

class JType: public Instruction {
    private:
        int op;
        std::string label;
        int immediate;

    public:
        JType(int op, std::string label);
        JType(int op, std::string label, int immediate);
        void print();
};

#endif