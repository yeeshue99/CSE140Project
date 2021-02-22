#include <iostream>
#include <string>
#include "JTypeInstruction.h"
#include "Decode.h"

using namespace std;

JType::JType(int op, string label){
    this->op = op;
    this->label = label;
    this->immediate = "";
}

JType::JType(int op, string label, string immediate){
    this->op = op;
    this->label = label;
    this->immediate = immediate;
}

void JType::print(){
    cout << "Instruction Type: J" << endl;
    cout << "Operation: " << label << endl;
    cout << "Address: 0000" << immediate << "00" << endl;
    cout << "Address: 0x" << convert_binary_to_hex(immediate) << endl;
}