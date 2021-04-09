#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <unordered_map>

using namespace std;

class Instruction {
    public:
        virtual void print(){};
        bool operator==(const int& rhs) const;
        virtual void writeBack(){};
        virtual void memory(){};
        virtual void execute(long registers[32], unordered_map<long long int, long long int> dmem, int &pc){};
        unsigned int str2int(const char *str, int h);
        virtual ~Instruction(){};
};

#endif