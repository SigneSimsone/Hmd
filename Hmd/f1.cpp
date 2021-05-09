/*******************************************
Signe Simsone, ss20120
H9. Doti divi faili bināri f1 un f2, kuru komponentes ir patvaļīgas simbolu virknes
(komponentes sakārtotas alfabētiski). Uzrakstīt programmu, kas apvieno failus f1 un f2 failā f3 tā,
lai arī f3 komponentes būtu sakārtotas (failā f3 nedrīkst parādīties divas komponentes ar vienādu vērtību).
Programmu veidot tā, lai pilns faila saturs netiktu ielādēts operatīvajā atmiņā. Uzrakstīt arī palīgprogrammas,
kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
*******************************************/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void WriteToFile(ofstream& output, int& size, string& string)
{
	output.write(reinterpret_cast<char*>(&size), sizeof(int));
	output.write(string.c_str(), size);
}

void ReadFile(ifstream& input, int& size, char*& buf, string& string)
{
	input.read(reinterpret_cast<char*>(&size), sizeof(int));
	buf = new char[size];
	input.read(buf, size);
	cout << buf << endl;

}

int main() {

	char* buf;

	int Count;
	int Size;

	ofstream Output("f1.bin", ios::out | ios::binary);
	if (!Output.is_open())
	{
		cout << "can't open file" << endl;
		exit(1);
	}

	cout << "How many strings in file f1?" << endl;
	cin >> Count;

	string* StringOfSymbols = new string[Count];

	cout << "Input strings:" << endl;
	for (int i = 0; i < Count; i++) {
		cin >> StringOfSymbols[i];
		Size = StringOfSymbols[i].size();
		WriteToFile(Output, Size, StringOfSymbols[i]);
	}

	Output.flush();
	Output.close();


	ifstream Input("f1.bin", ios::in | ios::binary);
	if (!Input.is_open())
	{
		cout << "can't open file" << endl;
		exit(1);
	}

	cout << endl;
	cout << "File f1 contains:" << endl;
	for (int i = 0; i < Count; i++) {
		ReadFile(Input, Size, buf, StringOfSymbols[i]);
	}

	Input.close();

	return 0;
}