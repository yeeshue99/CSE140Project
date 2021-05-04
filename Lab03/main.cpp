#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Decode.h"
#include "Instruction.h"
#include "R_Type.h"
#include "I_Type.h"
#include "J_Type.h"

using namespace std;

bool componentsAreEmpty(int instructionToFetch, string instructionToDecode, Instruction *instructionToExecute, Instruction *instructionToMemory, Instruction *instructionToWriteBack)
{
    return (instructionToFetch < 0) && instructionToDecode.empty() && (instructionToExecute == NULL) && (instructionToMemory == NULL) && (instructionToWriteBack == NULL);
}

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

    int instructionToFetch = -1;
    string instructionToDecode = "\0";
    Instruction *instructionAfterDecoding = NULL;
    Instruction *instructionToExecute = NULL;
    Instruction *instructionToMemory = NULL;
    Instruction *instructionToWriteBack = NULL;

    unsigned int oldPc = 0;
    unsigned int pc = 0;
    bool stillRunning = true;
    bool runOff = false;
    bool isStalling = false;

    unsigned int total_clock_cycles = 0;
    while (stillRunning)
    {
        if (instructionToExecute != NULL)
        {
            isStalling = checkStalling(instructionToExecute, instructionToMemory, instructionToMemory);
        }
        else
        {
            isStalling = false;
        }
        cout << "total_clock_cycles " << total_clock_cycles + 1 << " :" << endl;

#pragma region Active Operations
        if (!(instructionToWriteBack == NULL))
        {
            instructionToWriteBack->writeBack(registers, dmem);
        }

        if (!(instructionToMemory == NULL))
        {
            instructionToMemory->memory(registers, dmem);
        }

        if (!(instructionToExecute == NULL || isStalling))
        {
            instructionToExecute->execute(registers, dmem, pc);
        }

        if (!(instructionToDecode.empty() || isStalling))
        {
            instructionAfterDecoding = decode(instructionToDecode, registerSet, instructionSet);
            isStalling = checkStalling(instructionAfterDecoding, instructionToExecute, instructionToMemory);

            if (isStalling)
            {
                instructionToExecute = NULL;
            }
        }

#pragma endregion

#pragma region Advance Step
        instructionToFetch = pc;
        instructionToWriteBack = instructionToMemory;
        instructionToMemory = instructionToExecute;
        instructionToExecute = instructionAfterDecoding;
        if (instructionToDecode.empty())
        {
            instructionToExecute = NULL;
        }
        if (instructionToFetch >= 0 && !runOff && (instructionToFetch / 4 <= instructions.size() - 1))
        {
            instructionToDecode = instructions[instructionToFetch / 4];
        }
        else
        {
            instructionToDecode = "";
            instructionAfterDecoding = NULL;
        }

#pragma endregion

        if (oldPc != pc)
        {
            printf("Control Hazard Detected (flush 3 instructions)\n");
            instructionToDecode = "";
            instructionAfterDecoding = NULL;
            instructionToExecute = NULL;
        }

        if (!isStalling)
        {
            pc += 4;
        }
        else
        {
            printf("data hazard detected\n");
        }

        oldPc = pc;
        if (!(runOff || isStalling))
        {
            printf("pc is modified to %#x\n", pc);
        }
        total_clock_cycles++;
        if (pc / 4 >= instructions.size() - 1)
        {
            runOff = true;
        }

        if (runOff)
        {
            pc = -1;
            oldPc = pc;
            if (componentsAreEmpty(instructionToFetch, instructionToDecode, instructionToExecute, instructionToMemory, instructionToWriteBack))
            {
                stillRunning = false;
            }
        }
        cout << endl;
    }
    cout << "program terminated:" << endl;
    cout << "total execution time is " << total_clock_cycles << " cycles" << endl;

    return 0;
}