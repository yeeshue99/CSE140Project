#include <iostream>
#include <string>
#include "JTypeInstruction.h"

using namespace std;

JType::JType(int op, string label){
    this->op = op;
    this->label = label;
    this->immediate = 0;
}

JType::JType(int op, string label, int immediate){
    this->op = op;
    this->label = label;
    this->immediate = immediate;
}

void JType::print(){
    cout << "Intrsuction Type: J " << endl;
    cout << "Operation: " << label << endl;
    cout << "Immediate: " << immediate << endl;
}