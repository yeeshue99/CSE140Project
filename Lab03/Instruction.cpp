#include <iostream>
#include "Instruction.h"

void Instruction::print()
{
    std::cout << "Instruction!" << std::endl;
}

bool Instruction::operator==(const int &rhs) const
{
    return true;
}

void Instruction::writeBack()
{
}

void Instruction::memory()
{
}

void Instruction::execute(long registers[32], long dmem[32])
{
}