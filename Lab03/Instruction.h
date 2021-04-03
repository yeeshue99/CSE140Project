#ifndef INSTRUCTION_H
#define INSTRUCTION_H


class Instruction {
    public:
        void print();
        bool operator==(const int& rhs) const;
        void writeBack();
        void memory();
        void execute();
};

#endif