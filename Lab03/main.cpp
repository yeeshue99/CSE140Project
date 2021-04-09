#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Decode.h"
#include "Instruction.h"
#include "RTypeInstruction.h"
#include "ITypeInstruction.h"
#include "JTypeInstruction.h"

using namespace std;

int main(int argc, char *argv[])
{

    // Array with all registers
    long int registers[32];
    for (int i = 0; i < 32; i++)
    {
        registers[i] = 0;
    }

    // $t1 = 0x20 (32)
    // $t2 = 0x5 (5)
    // $s0 = 0x70 (112)
    registers[9] = 32;
    registers[10] = 5;
    registers[16] = 112;

    // Array with all dynamic memory
    unordered_map<long long int, long long int> dmem;

    // 0x70 = 0x5 ([112] = 5)
    // 0x74 = 0x10 ([116] = 16)
    dmem[112] = 5;
    dmem[116] = 16;

    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile)
    {
        cerr << "Unable to open file: input.txt";
        exit(1); // call system to stop
    }

    // Vector with all instructions in order
    vector<string> instructions;
    string binaryIn;
    while (getline(inFile, binaryIn))
    {
        instructions.push_back(binaryIn);
    }

    inFile.close();

    unordered_map<string, string> instructionSet;
    instructionSet = load_instruction_file("instructions.txt");

    unordered_map<long long int, string> registerSet;
    registerSet = load_register_file("registers.txt");

    int instructionToFetch;
    string instructionToDecode;
    Instruction *instructionAfterDecoding;
    Instruction *instructionToExecute = NULL;
    Instruction *instructionToMemory;
    Instruction *instructionToWriteBack;

    int pc = 0;
    bool stillRunning = true;
    bool isStalling = false;
    while (stillRunning)
    {
        /*
#pragma region Active Operations

        if (!(instructionToWriteBack == NULL))
        {
            instructionToWriteBack.writeBack();
        }

        if (!(instructionToMemory == NULL))
        {
            instructionToMemory.memory();
        }

        if (!(instructionToExecute == NULL))
        {
            instructionToExecute.execute();
        }

        if (!instructionToDecode.empty())
        {
            instructionToExecute.decode();
        }

        instructionToFetch = pc / 4;
#pragma endregion

#pragma region Advance Step
        instructionToWriteBack = instructionToMemory;
        instructionToMemory = instructionToExecute;
        instructionToExecute = instructionAfterDecoding;
        instructionToDecode = instructions[instructionToFetch];
        instructionToFetch = pc;
#pragma endregion
*/
        instructionToFetch = pc / 4;
        instructionToDecode = instructions[instructionToFetch];
        // if (instructionToExecute != NULL)
        // {
        //     delete instructionToExecute;
        //     instructionToExecute = NULL;
        // }

        instructionToExecute = decode(instructionToDecode, registerSet, instructionSet);
        instructionToExecute->execute(registers, dmem, pc);
        //instructionToExecute->print();
        pc += 4;
        // Do logic here.
        if (pc / 4 >= instructions.size() /* && with checking if all components are empty*/)
        {
            stillRunning = false;
        }
        cout << endl;
    }
    return 0;
}