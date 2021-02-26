#ifndef RTYPE_H
#define RTYPE_H

#include "Instruction.h"
#include <string>

class RType: public Instruction {
    private:
        int op;
        std::string label;
        std::string rs;
        std::string rt;
        std::string rd;
        std::string shamt;
        int func;
        std::map<std::string, std::string> registerMap;

    public:
        RType(int op, std::string label, int func);
        RType(int op, std::string label, std::string rs, std::string rt, std::string rd, std::string shamt, 
        int func, std::map<std::string, std::string>);
        void print();
};

#endif