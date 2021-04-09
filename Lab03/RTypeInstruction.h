#ifndef RTYPE_H
#define RTYPE_H

#include "Instruction.h"
#include <string>

using namespace std;

class RType: public Instruction {
    private:
        int op;
        string label;
        string rs;
        string rt;
        string rd;
        string shamt;
        int func;
        map<string, string> registerMap;

    public:
        RType(int op, string label, int func);
        RType(int op, string label, string rs, string rt, string rd, string shamt, 
        int func, map<string, string>);
        void print();
        void execute(long registers[32], long dmem[32]);
};

#endif