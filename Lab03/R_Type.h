#ifndef RTYPE_H
#define RTYPE_H

#include "Instruction.h"
#include "Decode.h"
#include <string>

using namespace std;

class RType : public Instruction
{
private:
    int op;
    string label;
    long long int rs = -1;
    long long int rt = -1;
    long long int rd = -1;
    long long int shamt;
    int func;
    unordered_map<long long int, string> registerMap;
    long val;

public:
    RType(int op, string label, int func);
    RType(int op, string label, long long int rs, long long int rt, long long int rd, long long int shamt,
          int func, unordered_map<long long int, string> registerMap);
    void print();
    void execute(long registers[32], unordered_map<long long int, long long int> dmem, unsigned int &pc);
    void writeBack(long registers[32], unordered_map<long long int, long long int> dmem);
    void memory(long registers[32], unordered_map<long long int, long long int> dmem);

    long long int getRS();
    long long int getRT();
    long long int getRD();
};

#endif