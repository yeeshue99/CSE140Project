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

    // pc
    int pc = 0;
    bool stillRunning = true;
    while (stillRunning)
    {

        //if(!isStalling) fetch(pc);
        //if(!isStalling) decode();
        //execute();
        //memory();
        //writeback();

        if (pc >= instructions.size() /* && with checking if all components are empty*/)
        {
            stillRunning = false;
        }
    }

    // Command that is in each stage

    // track each instruction in each stage

    //cout << "Enter the binary number: ";
    while (getline(inFile, binaryIn))
    {
        cout << endl;
        cout << "Input: " << binaryIn << endl;
        std::map<std::string, std::string> instructionSet;
        instructionSet = load_instruction_file("instructions.txt");

        std::map<std::string, std::string> registerSet;
        registerSet = load_register_file("registers.txt");

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
            ins.print();
            continue;
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
            ins.print();
            continue;
        }

        key = "j" + firstSix;
        if (instructionSet.count(key) > 0)
        {
            string label;
            label = instructionSet[key];
            long int opcode = convert_binary_to_hex(stoi(binaryIn.substr(0, 6)));

            string address = binaryIn.substr(6, 26);
            JType ins = JType(opcode, label, address);
            ins.print();
            continue;
        }
        else
        {
            cout << "Instruction not found!" << endl;
            continue;
        }
    }

    inFile.close();

    //long int binaryInt = stoi(binaryIn);
    //cout << "Equivalent hexadecimal value: " << convert_binary_to_hex(binaryInt) << endl;

    return 0;
}