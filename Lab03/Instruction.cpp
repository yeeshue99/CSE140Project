#include <iostream>
#include "Instruction.h"

using namespace std;

unsigned int Instruction::str2int(const char *str, int h)
{
    return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}