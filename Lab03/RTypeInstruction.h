#ifndef RTYPE_H
#define RTYPE_H

#include "Instruction.h"
#include "Decode.h"
#include <string>

using namespace std;

class RType: public Instruction {
    private:
        int op;
        string label;
        long long int rs;
        long long int rt;
        long long int rd;
        long long int shamt;
        int func;
        unordered_map<long long int, string> registerMap;

    public:
        RType(int op, string label, int func);
        RType(int op, string label, long long int rs, long long int rt, long long int rd, long long int shamt,
             int func, unordered_map<long long int, string> registerMap);
        virtual void print();
        virtual void execute(long registers[32], unordered_map<long long int, long long int> dmem, int & pc);
};

#endif