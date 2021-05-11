#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class StringOfSymbols
{
private:
    string String;

public:

    StringOfSymbols(string InputString) {
        String = InputString;
    };
   
    void fillObject() {
        string InputString;

        cout << "Input strings: " << endl;
        cin >> InputString;

        StringOfSymbols(InputString);
    };
    
    void write(ostream& fout) {
        fout.write((char*)this, sizeof(StringOfSymbols));
    };;
    
    bool read(istream& fin) {
        fin.read((char*)this, sizeof(StringOfSymbols));
        return (bool)fin;
    };;
    
    void print() {
        cout << String << endl;
    };;
};
int main()
{
    ofstream fout1;
    ifstream fin1;
    StringOfSymbols element;

    fout1.open("stud.bin", ios::binary);

    element.fillObject();
    while (!cin.eof())
    {
        element.write(fout1);
        element.fillObject();
    };

    fout1.close();


    fin1.open("stud.bin", ios::binary);
    while (element.read(fin1)) {
        element.print();
    }
    fin1.close();
    return 0;
};