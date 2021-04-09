#ifndef DECODE_H
#define DECODE_H

#include <map>
#include <unordered_map>
#include <string>
#include "Instruction.h"

using namespace std;

long int convert_binary_to_hex(long int binary);
string convert_binary_to_hex(string bin);
string convert_binary_to_hex_to_dec(string bin);
void createMap(unordered_map<string, char> *um);
bool is_r_type_instruction(long int binary);
map<string, string> load_instruction_file(string filename); 
map<string, string> load_register_file(string filename);
Instruction decode(string binaryIn, map<string, string> registerSet, map<string, string> instructionSet);
#endif