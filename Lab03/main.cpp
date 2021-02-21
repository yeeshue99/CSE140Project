#include <iostream>
#include <fstream>
#include <string> 
#include <map>
#include "Decode.h"
#include "Instruction.h"
#include "RTypeInstruction.h"
#include "ITypeInstruction.h"
#include "JTypeInstruction.h"

using namespace std;

int main(int argc, char *argv[])
{

    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile)
    {
        cerr << "Unable to open file: input.txt";
        exit(1); // call system to stop
    }

    string binaryIn;

    //cout << "Enter the binary number: ";

    getline(inFile, binaryIn);

    inFile.close();

    cout << "Input: " << binaryIn << endl;
    std::map<std::string, std::string> instructionSet;
    instructionSet = load_instruction_file("instructions.txt");

    std::map<std::string, std::string> registerSet;
    registerSet = load_register_file("registers.txt");

    cout << convert_binary_to_hex(1010, true) << endl;

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

        string rs = convert_binary_to_hex(stoi(binaryIn.substr(6, 5)), true);
        string rt = convert_binary_to_hex(stoi(binaryIn.substr(11, 5)), true);
        string rd = convert_binary_to_hex(stoi(binaryIn.substr(16, 5)), true);
        int shamt = convert_binary_to_hex(stoi(binaryIn.substr(21, 5)));

        RType ins = RType(0, label, rs, rt, rd, shamt, convert_binary_to_hex(lastSix), registerSet);
        ins.print();
    }

    key = "i" + firstSix;
    else if (instructionSet.count(key) > 0)
    {
        string label;
        label = instructionSet[key];

        long int opcode = convert_binary_to_hex(stoi(binaryIn.substr(0, 6)));
        string rs = convert_binary_to_hex(stoi(binaryIn.substr(6, 5)), true);
        string rt = convert_binary_to_hex(stoi(binaryIn.substr(11, 5)), true);
        int imm = convert_binary_to_hex(stoi(binaryIn.substr(16, 16)));

        IType ins = IType(opcode, label, rs, rt, imm, registerSet);
        ins.print();
    }
    
    key = "j" + firstSix;
    else if (instructionSet.count(key) > 0){
        string label;
        label = instructionSet[key];
        long int opcode = convert_binary_to_hex(stoi(binaryIn.substr(0, 6)));

        string address = binaryIn.substr(6, 26)
    }
    else{
        cout << "Instruction not found!" << endl;
    }


    //long int binaryInt = stoi(binaryIn);
    //cout << "Equivalent hexadecimal value: " << convert_binary_to_hex(binaryInt) << endl;

    return 0;
}