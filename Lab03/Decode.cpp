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
#include <unordered_map>

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

string convert_binary_to_hex(string bin)
{
    {
    int l = bin.size();
    int t = bin.find_first_of('.');
     
    // length of string before '.'
    int len_left = t != -1 ? t : l;
     
    // add min 0's in the beginning to make
    // left substring length divisible by 4 
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
        bin = '0' + bin;
     
    // if decimal point exists    
    if (t != -1)    
    {
        // length of string after '.'
        int len_right = l - len_left - 1;
         
        // add min 0's in the end to make right
        // substring length divisible by 4 
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
            bin = bin + '0';
    }
     
    // create map between binary and its
    // equivalent hex code
    unordered_map<string, char> bin_hex_map;
    createMap(&bin_hex_map);
     
    int i = 0;
    string hex = "";
     
    while (1)
    {
        // one by one extract from left, substring
        // of size 4 and add its hex code
        hex += bin_hex_map[bin.substr(i, 4)];
        i += 4;
        if (i == bin.size())
            break;
             
        // if '.' is encountered add it
        // to result
        if (bin.at(i) == '.')    
        {
            hex += '.';
            i++;
        }
    }
     
    // required hexadecimal number
    return hex;    
}
}

void createMap(unordered_map<string, char> *um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'A';
    (*um)["1011"] = 'B';
    (*um)["1100"] = 'C';
    (*um)["1101"] = 'D';
    (*um)["1110"] = 'E';
    (*um)["1111"] = 'F';
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

std::map<std::string, std::string> load_instruction_file(std::string filename)
{
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

std::map<std::string, std::string> load_register_file(std::string filename)
{
    map<std::string, std::string> registermap;

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

        key = results[0];
        
        registermap.insert(std::pair<std::string, std::string>(key, results[1]));

        //cout << key << " => " << instructionMap[key] << '\n';
    }

    return registermap;
}

