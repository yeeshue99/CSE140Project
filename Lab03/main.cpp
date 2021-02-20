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

    std::cout << instructionSet.size() << std::endl;

    long int firstSix = stoi(binaryIn.substr(0, 6));
    if (is_r_type_instruction(firstSix))
    {
        string key = "r";
        key.append(binaryIn.substr(binaryIn.size() - 7));
        key.pop_back();

        string label;
        label = instructionSet[key];
        
        
        
        long int lastSix = stoi(binaryIn.substr(binaryIn.size() - 7));
        RType ins = RType(0, label, convert_binary_to_hex(lastSix));
        ins.print();
    }

    //long int binaryInt = stoi(binaryIn);
    //cout << "Equivalent hexadecimal value: " << convert_binary_to_hex(binaryInt) << endl;

    return 0;
}