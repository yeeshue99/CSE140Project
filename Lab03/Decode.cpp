#include <string> 
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <iterator>
#include "Decode.h"
#include "Instruction.h"
#include "RTypeInstruction.h"
#include "ITypeInstruction.h"
#include "JTypeInstruction.h"

using namespace std;

long int convert_binary_to_hex(long int binary)
{
    string hex = "";
    long int dec = 0, i = 1, remainder;
    while (binary != 0)
    {
        remainder = binary % 10;
        dec = dec + remainder * i;
        i = i * 2;
        binary = binary / 10;
    }

    while (dec != 0)
    {
        hex.insert(0, to_string(dec % 16));
        dec = dec / 16;
    }


    if(hex.size() == 0){
        hex = "0";
    }

    return stoi(hex);
}

bool is_r_type_instruction(long int binary)
{
    long int hex = convert_binary_to_hex(binary);
    if (hex == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::map<std::string, std::string> load_instruction_file(std::string filename){
    map<std::string, std::string> instructionMap;

    ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        cerr << "Unable to open file: " << filename;
        exit(1); // call system to stop
    }
    string line;
    string key;

    while (getline(inFile,line) )
    {
        std::istringstream iss(line);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());

        key = results[0] + results[2];
        
        instructionMap.insert(std::pair<std::string, std::string>(key, results[1]));

        //cout << key << " => " << instructionMap[key] << '\n';
    }

    return instructionMap;
}



