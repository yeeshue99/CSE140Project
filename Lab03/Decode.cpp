#include <iostream>
#include <fstream>
#include <string> 
#include <map>

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


    if(hex.size() == 0){
        hex = "0";
    }

    return stoi(hex);
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

int main(int argc, char *argv[])
{

    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1); // call system to stop
    }

    string binaryIn;

    //cout << "Enter the binary number: ";

    getline(inFile, binaryIn);

    inFile.close();

    cout << "Input: " << binaryIn << endl;

    long int firstSix = stoi(binaryIn.substr(0, 6));
    if (is_r_type_instruction(firstSix))
    {
        cout << "Opcode: " << firstSix << " hex" << endl;

        long int lastSix = stoi(binaryIn.substr(binaryIn.size() - 6));
        //cout << lastSix << endl;
        cout << "Function Code: " << convert_binary_to_hex(lastSix) << " hex" << endl;
    }

    //long int binaryInt = stoi(binaryIn);
    //cout << "Equivalent hexadecimal value: " << convert_binary_to_hex(binaryInt) << endl;

    return 0;
}
