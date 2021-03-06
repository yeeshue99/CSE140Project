#include <iostream>
#include <string>
#include <unordered_map>
#include "R_Type.h"

using namespace std;

RType::RType(int op, string label, int func)
{
    this->op = op;
    this->label = label;
    this->rs = 0;
    this->rt = 0;
    this->rd = 0;
    this->shamt = 0;
    this->func = func;
}

RType::RType(int op, string label, long long int rs, long long int rt, long long int rd, long long int shamt,
             int func, unordered_map<long long int, string> registerMap)
{
    this->op = op;
    this->label = label;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->shamt = shamt;
    this->func = func;
    this->registerMap = registerMap;
}

void RType::print()
{
    cout << "Instruction Type: R " << endl;
    cout << "Operation: " << label << endl;
    cout << "Rs: " << registerMap[rs] << " (R" << rs << ")" << endl;
    cout << "Rt: " << registerMap[rt] << " (R" << rt << ")" << endl;
    cout << "Rd: " << registerMap[rd] << " (R" << rd << ")" << endl;
    cout << "Shamt: 0x" << shamt << endl;
    cout << "Func: 0x" << func << endl;
}

void RType::execute(long registers[32], unordered_map<long long int, long long int> dmem, unsigned int &pc)
{
    unsigned int strHash = this->str2int(label.c_str(), 0);

    if (strHash == this->str2int("add", 0))
    {
        //cout << "ADD" << endl;
        val = registers[rs] + registers[rt];
        //registers[rd] = val;
        //printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("sub", 0))
    {
        //cout << "SUB" << endl;
        val = registers[rs] - registers[rt];
        //registers[rd] = val;
        //printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("and", 0))
    {
        //cout << "AND" << endl;
        val = registers[rs] & registers[rt];
        //registers[rd] = val;
        //printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("or", 0))
    {
        //cout << "OR" << endl;
        val = registers[rs] | registers[rt];
        //registers[rd] = val;
        //printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("slt", 0))
    {
        //cout << "SLT" << endl;
        val = registers[rs] < registers[rt] ? 1 : 0;
        //registers[rd] = val;
        if (!val)
        {
            //printf("$%s is modified to 0x0\n", registerMap[rd].c_str());
        }
        else
        {
            //printf("$%s is modified to %02lx\n", registerMap[rd].c_str(), val);
        }

        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("nor", 0))
    {
        //cout << "NOR" << endl;
        val = ~(registers[rs] | registers[rt]);
        //registers[rd] = val;
        //printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
}

void RType::writeBack(long registers[32], unordered_map<long long int, long long int> dmem)
{
}

void RType::memory(long registers[32], unordered_map<long long int, long long int> dmem)
{
    unsigned int strHash = this->str2int(label.c_str(), 0);

    if (strHash == this->str2int("add", 0))
    {
        //cout << "ADD" << endl;
        registers[rd] = val;
        printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("sub", 0))
    {
        //cout << "SUB" << endl;
        registers[rd] = val;
        printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("and", 0))
    {
        //cout << "AND" << endl;
        registers[rd] = val;
        printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("or", 0))
    {
        //cout << "OR" << endl;
        registers[rd] = val;
        printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("slt", 0))
    {
        //cout << "SLT" << endl;
        registers[rd] = val;
        if (!val)
        {
            printf("$%s is modified to 0x0\n", registerMap[rd].c_str());
        }
        else
        {
            printf("$%s is modified to %02lx\n", registerMap[rd].c_str(), val);
        }

        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
    else if (strHash == this->str2int("nor", 0))
    {
        //cout << "NOR" << endl;
        registers[rd] = val;
        printf("$%s is modified to %#lx\n", registerMap[rd].c_str(), val);
        //cout << registerMap[rd] << " is modified to " << val << endl;
    }
}

long long int RType::getRS()
{
    return rs;
}
long long int RType::getRT()
{
    return rt;
}
long long int RType::getRD()
{
    return rd;
}