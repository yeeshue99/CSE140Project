#include <iostream>
#include <string>
#include <unordered_map>
#include "I_Type.h"

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

void IType::execute(long registers[32], unordered_map<long long int, long long int> dmem, unsigned int &pc)
{
    unsigned int strHash = this->str2int(label.c_str(), 0);

    if (strHash == this->str2int("lw", 0))
    {
        //cout << "LW" << endl;

        //printf("$%s is modified to %#llx\n", registerMap[rt].c_str(), dmem[dMemLocation]);

        //cout << registerMap[rt] << " is modified to " << dmem[dMemLocation] << endl;
    }
    else if (strHash == this->str2int("sw", 0))
    {
        //cout << "SW" << endl;
        //long dMemLocation = registers[rs] + immediate;

        //if (dmem.count(dMemLocation) <= 0)
        //{
        //dmem[dMemLocation] = 0;
        //}

        //dmem[dMemLocation] = registers[rt];

        //printf("Memory %#lx is modified to %#lx\n", dMemLocation, registers[rt]);

        //cout << "memory " << dMemLocation << " is modified to " << registers[rt] << endl;
    }
    else if (strHash == this->str2int("beq", 0))
    {
        //cout << "BEQ" << endl;
        if (registers[rs] == registers[rt])
        {
            pc = pc + (immediate)*4;
            //cout << "pc is modified to " << pc << endl;
        }
    }
}

void IType::writeBack(long registers[32], unordered_map<long long int, long long int> dmem)
{
    unsigned int strHash = this->str2int(label.c_str(), 0);

    if (strHash == this->str2int("lw", 0))
    {
        //cout << "LW" << endl;
        long dMemLocation = registers[rs] + immediate;

        if (dmem.count(dMemLocation) <= 0)
        {
            dmem[dMemLocation] = 0;
        }

        registers[rt] = dmem[dMemLocation];

        printf("$%s is modified to %#llx\n", registerMap[rt].c_str(), dmem[dMemLocation]);

        //cout << registerMap[rt] << " is modified to " << dmem[dMemLocation] << endl;
    }
    else if (strHash == this->str2int("sw", 0))
    {
    }
    else if (strHash == this->str2int("beq", 0))
    {
    }
}

void IType::memory(long registers[32], unordered_map<long long int, long long int> dmem)
{
    unsigned int strHash = this->str2int(label.c_str(), 0);

    if (strHash == this->str2int("lw", 0))
    {
    }
    else if (strHash == this->str2int("sw", 0))
    {
        //cout << "SW" << endl;
        long dMemLocation = registers[rs] + immediate;

        if (dmem.count(dMemLocation) <= 0)
        {
            dmem[dMemLocation] = 0;
        }

        dmem[dMemLocation] = registers[rt];

        printf("Memory %#lx is modified to %#lx\n", dMemLocation, registers[rt]);

        //cout << "memory " << dMemLocation << " is modified to " << registers[rt] << endl;
    }
    else if (strHash == this->str2int("beq", 0))
    {
    }
}

long long int IType::getRS()
{
    return rs;
}
long long int IType::getRT()
{
    return rt;
}
long long int IType::getRD()
{
    return -1;
}