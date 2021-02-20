#include <iostream>
#include <string>
#include "ITypeInstruction.h"

using namespace std;

IType::IType(int op, string label){
    this->op = op;
    this->label = label;
    this->rs = 0;
    this->rt = 0;
    this->immediate = 0;
}

IType::IType(int op, string label, int rs, int rt, int immediate){
    this->op = op;
    this->label = label;
    this->rs = rs;
    this->rt = rt;
    this->immediate = immediate;
}

void IType::print(){
    cout << "Intrsuction Type: I " << endl;
    cout << "Operation: " << label << endl;
    cout << "Rs: " << rs << endl;
    cout << "Rt: " << rt << endl;
    cout << "immediate: " << immediate << endl;
}