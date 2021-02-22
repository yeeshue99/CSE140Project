#ifndef DECODE_H
#define DECODE_H

#include <map>
#include <unordered_map>
#include <string>

long int convert_binary_to_hex(long int binary);
std::string convert_binary_to_hex(std::string bin);
void createMap(std::unordered_map<std::string, char> *um);
bool is_r_type_instruction(long int binary);
std::map<std::string, std::string> load_instruction_file(std::string filename); 
std::map<std::string, std::string> load_register_file(std::string filename);
#endif