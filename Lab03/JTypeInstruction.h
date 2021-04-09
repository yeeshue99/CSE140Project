#ifndef JTYPE_H
#define JTYPE_H

#include "Instruction.h"
#include <string>

using namespace std;

class JType: public Instruction {
    private:
        int op;
        string label;
        string immediate;

    public:
        JType(int op, string label);
        JType(int op, string label, string immediate);
        void print();
        void execute(long registers[32], long dmem[32]);
};

#endif