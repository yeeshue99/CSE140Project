#include <iostream>
#include <string>
#include <map>
#include "RTypeInstruction.h"

using namespace std;

RType::RType(int op, string label, int func){
    this->op = op;
    this->label = label;
    this->rs = "";
    this->rt = "";
    this->rd = "";
    this->shamt = 0;
    this->func = func;
}

RType::RType(int op, string label, string rs, string rt, string rd, int shamt, 
int func, map<string, string> registerMap){
    this->op = op;
    this->label = label;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->shamt = shamt;
    this->func = func;
    this->registerMap = registerMap;
}

void RType::print(){
    cout << "Instruction Type: R " << endl;
    cout << "Operation: " << label << endl;
    cout << "Rs: " << registerMap[rs] << " (R" << rs << ")" << endl;
    cout << "Rt: " << registerMap[rt] << " (R" << rt << ")" << endl;
    cout << "Rd: " << registerMap[rd] << " (R" << rd << ")" << endl;
    cout << "Shamt: " << shamt <<  endl;
    cout << "Func: 0x" << func << endl;
}