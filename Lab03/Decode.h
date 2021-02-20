#ifndef DECODE_H
#define DECODE_H

#include <map>
#include <string>

long int convert_binary_to_hex(long int binary);
bool is_r_type_instruction(long int binary);
std::map<std::string, std::string> load_instruction_file(std::string filename); 

#endif