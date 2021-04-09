#ifndef DECODE_H
#define DECODE_H

#include <map>
#include <unordered_map>
#include <string>
#include "Instruction.h"

long int convert_binary_to_hex(long int binary);
std::string convert_binary_to_hex(std::string bin);
std::string convert_binary_to_hex_to_dec(std::string bin);
void createMap(std::unordered_map<std::string, char> *um);
bool is_r_type_instruction(long int binary);
std::map<std::string, std::string> load_instruction_file(std::string filename); 
std::map<std::string, std::string> load_register_file(std::string filename);
Instruction decode(std::string binaryIn, std::map<std::string, std::string> registerSet, std::map<std::string, std::string> instructionSet);
#endif