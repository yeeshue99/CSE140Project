#include <iostream>
#include <string>
#include <unordered_map>
#include "ITypeInstruction.h"

using namespace std;

IType::IType(int op, string label)
{
    this->op = op;
    this->label = label;
    this->rs = 0;
    this->rt = 0;
    this->immediate = 0;
}

IType::IType(int op, string label, long long int rs, long long int rt, long long int immediate, unordered_map<long long int, string> registerMap)
{
    this->op = op;
    this->label = label;
    this->rs = rs;
    this->rt = rt;
    this->immediate = immediate;
    this->registerMap = registerMap;
}

void IType::print()
{
    cout << "Instruction Type: I " << endl;
    cout << "Operation: " << label << endl;
    cout << "Rs: " << registerMap[rs] << " (R" << rs << ")" << endl;
    cout << "Rt: " << registerMap[rt] << " (R" << rt << ")" << endl;
    cout << "Immediate: 0x" << immediate << endl;
}

void IType::execute(long registers[32], unordered_map<long long int, long long int> dmem, int &pc)
{
    unsigned int strHash = this->str2int(label.c_str(), 0);

    if (strHash == this->str2int("lw", 0))
    {
        cout << "LW" << endl;
        long dMemLocation = registers[rs] + rt;

        registers[rt] = dmem[dMemLocation];
    }
    else if (strHash == this->str2int("sw", 0))
    {
        cout << "SW" << endl;
    }
    else if (strHash == this->str2int("beq", 0))
    {
        cout << "BEQ" << endl;
    }
}