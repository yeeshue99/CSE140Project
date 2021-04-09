#ifndef ITYPE_H
#define ITYPE_H

#include "Instruction.h"
#include "Decode.h"
#include <string>

using namespace std;

class IType: public Instruction {
    private:
        int op;
        string label;
        long long int rs;
        long long int rt;
        long long int immediate;
        unordered_map<long long int, string> registerMap;

    public:
        IType(int op, string label);
        IType(int op, string label, long long int rs, long long int rt, long long int immediate, unordered_map<long long int, string> registerMap);
        virtual void print();
        void execute(long registers[32], unordered_map<long long int, long long int> dmem, int & pc);
};

#endif