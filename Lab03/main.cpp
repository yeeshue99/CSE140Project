#include <iostream>
#include <fstream>
#include <string>
#include <map>
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
    long int dmem[32];
    for (int i = 0; i < 32; i++)
    {
        dmem[i] = 0;
    }

    // 0x70 = 0x5 ([28] = 5)
    // 0x74 = 0x10 ([29] = 16)
    dmem[28] = 5;
    dmem[29] = 16;

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

    std::map<std::string, std::string> instructionSet;
    instructionSet = load_instruction_file("instructions.txt");

    std::map<std::string, std::string> registerSet;
    registerSet = load_register_file("registers.txt");

    int instructionToFetch;
    std::string instructionToDecode;
    Instruction instructionAfterDecoding;
    Instruction instructionToExecute;
    Instruction instructionToMemory;
    Instruction instructionToWriteBack;

    int pc = 0;
    bool stillRunning = true;
    bool isStalling = false;
    while (stillRunning)
    {
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
            string firstSix = binaryIn.substr(0, 6);
            string key;

            if (is_r_type_instruction(stoi(firstSix)))
            {
                key = "r";
                key.append(binaryIn.substr(binaryIn.size() - 7));
                key.pop_back();

                string label;
                label = instructionSet[key];

                long int lastSix = stoi(binaryIn.substr(binaryIn.size() - 7));

                string rs = convert_binary_to_hex_to_dec(binaryIn.substr(6, 5));
                string rt = convert_binary_to_hex_to_dec(binaryIn.substr(11, 5));
                string rd = convert_binary_to_hex_to_dec(binaryIn.substr(16, 5));
                string shamt = convert_binary_to_hex(binaryIn.substr(21, 5));

                RType ins = RType(0, label, rs, rt, rd, shamt, convert_binary_to_hex(lastSix), registerSet);
                instructionAfterDecoding = ins;
            }

            key = "i" + firstSix;
            if (instructionSet.count(key) > 0)
            {
                string label;
                label = instructionSet[key];

                long int opcode = convert_binary_to_hex(stoi(binaryIn.substr(0, 6)));
                string rs = convert_binary_to_hex_to_dec(binaryIn.substr(6, 5));
                string rt = convert_binary_to_hex_to_dec(binaryIn.substr(11, 5));
                string imm = convert_binary_to_hex(binaryIn.substr(16, 16));

                IType ins = IType(opcode, label, rs, rt, imm, registerSet);
                instructionAfterDecoding = ins;
            }

            key = "j" + firstSix;
            if (instructionSet.count(key) > 0)
            {
                string label;
                label = instructionSet[key];
                long int opcode = convert_binary_to_hex(stoi(binaryIn.substr(0, 6)));

                string address = binaryIn.substr(6, 26);
                JType ins = JType(opcode, label, address);
                instructionAfterDecoding = ins;
            }
            else
            {
                cout << "Instruction not found!" << endl;
                return -1;
            }
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
        if (pc >= instructions.size() /* && with checking if all components are empty*/)
        {
            stillRunning = false;
        }
    }
    return 0;
}