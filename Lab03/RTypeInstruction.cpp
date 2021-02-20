#include <iostream>
#include <string>
#include "RTypeInstruction.h"

using namespace std;

RType::RType(int op, string label, int func){
    this->op = op;
    this->label = label;
    this->rs = 0;
    this->rt = 0;
    this->rd = 0;
    this->shamt = 0;
    this->func = func;
}

RType::RType(int op, string label, int rs, int rt, int rd, int shamt, int func){
    this->op = op;
    this->label = label;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->shamt = shamt;
    this->func = func;
}

void RType::print(){
    cout << "Instruction Type: R " << endl;
    cout << "Operation: " << label << endl;
    cout << "Rs: " << rs << endl;
    cout << "Rt: " << rt << endl;
    cout << "Rd: " << rd << endl;
    cout << "Shamt: " << shamt << endl;
    cout << "Func: " << func << endl;
}