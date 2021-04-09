#ifndef INSTRUCTION_H
#define INSTRUCTION_H


class Instruction {
    public:
        void print();
        bool operator==(const int& rhs) const;
        void writeBack();
        void memory();
        void execute(long registers[32], long dmem[32]);
};

#endif