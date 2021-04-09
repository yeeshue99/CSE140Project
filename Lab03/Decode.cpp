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

    if (hex.size() == 0)
    {
        hex = "0";
    }

    return stoi(hex);
}

string convert_binary_to_hex_to_dec(string bin)
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

        unsigned int x;
        stringstream ss;
        ss << hex << hex;
        ss >> x;
        hex = to_string(x);

        // required hexadecimal number
        return hex;
    }
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

map<string, string> load_instruction_file(string filename)
{
    map<string, string> instructionMap;

    ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        cerr << "Unable to open file: " << filename;
        exit(1); // call system to stop
    }
    string line;
    string key;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        vector<string> results(istream_iterator<string>{iss},
                               istream_iterator<string>());

        key = results[0] + results[2];

        instructionMap.insert(pair<string, string>(key, results[1]));

        //cout << key << " => " << instructionMap[key] << '\n';
    }

    return instructionMap;
}

map<string, string> load_register_file(string filename)
{
    map<string, string> registermap;

    ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        cerr << "Unable to open file: " << filename;
        exit(1); // call system to stop
    }
    string line;
    string key;

    while (getline(inFile, line))
    {
        istringstream iss(line);
        vector<string> results(istream_iterator<string>{iss},
                               istream_iterator<string>());

        key = results[0];

        registermap.insert(pair<string, string>(key, results[1]));

        //cout << key << " => " << instructionMap[key] << '\n';
    }

    return registermap;
}

Instruction decode(string binaryIn, map<string, string> registerSet, map<string, string> instructionSet)
{
    string firstSix = binaryIn.substr(0, 6);
    string key;
    Instruction instructionAfterDecoding;
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
        return instructionAfterDecoding;
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
        return instructionAfterDecoding;
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
        return instructionAfterDecoding;
    }
    else
    {
        cout << "Instruction not found!" << endl;
        return Instruction();
    }
}