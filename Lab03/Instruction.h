#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <unordered_map>

using namespace std;

class Instruction
{
public:
    virtual void print(){};
    bool operator==(const int &rhs) const;
    virtual void writeBack(long registers[32], unordered_map<long long int, long long int> dmem){};
    virtual void memory(long registers[32], unordered_map<long long int, long long int> dmem){};
    virtual void execute(long registers[32], unordered_map<long long int, long long int> dmem, unsigned int &pc){};
    unsigned int str2int(const char *str, int h);

    virtual long long int getRS() = 0;
    virtual long long int getRT() = 0;
    virtual long long int getRD() = 0;

    virtual ~Instruction(){};
};

#endif