#include <iostream>
#include <string>
#include <map>
#include "ITypeInstruction.h"

using namespace std;

IType::IType(int op, string label)
{
    this->op = op;
    this->label = label;
    this->rs = "";
    this->rt = "";
    this->immediate = "";
}

IType::IType(int op, string label, string rs, string rt, string immediate, map<string, string> registerMap)
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

void IType::execute(long registers[32], long dmem[32])
{
}