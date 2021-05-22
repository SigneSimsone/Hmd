/*******************************************
Signe Simsone, ss20120
H9. Doti divi faili bināri f1 un f2, kuru komponentes ir patvaļīgas simbolu virknes
(komponentes sakārtotas alfabētiski). Uzrakstīt programmu, kas apvieno failus f1 un f2 failā f3 tā,
lai arī f3 komponentes būtu sakārtotas (failā f3 nedrīkst parādīties divas komponentes ar vienādu vērtību).
Programmu veidot tā, lai pilns faila saturs netiktu ielādēts operatīvajā atmiņā. Uzrakstīt arī palīgprogrammas,
kas ļauj izveidot failus f1 un f2 un izdrukā failu saturu.
Programma izveidota: 03/05/2021
*******************************************/
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

class FileParser
{
private:
	list<string> StringOfSymbols;

public:
	FileParser() {
	};

	void fillObjectForMergedFiles(list<string>fileContents) {
		StringOfSymbols = fileContents;
	};

	void fillObject() {
		string InputString;
		cin >> InputString;
		if (InputString != "") {
			StringOfSymbols.push_back(InputString);
			StringOfSymbols.sort();
		}
	};

	void write(ostream& fout) {
		list <string> ::iterator it;
		for (it = StringOfSymbols.begin(); it != StringOfSymbols.end(); ++it) {
			unsigned int size = (*it).size();
			fout.write(reinterpret_cast<char*>(&size), sizeof(size));
			fout.write((*it).c_str(), size);
		}
	};

	bool read(istream& fin) {
		//clear list, then read information from file into it
		/*if (StringOfSymbols.size() > 0) {
			StringOfSymbols.clear();
		}*/

		unsigned int size = 0;

		while (!fin.eof()) {
			fin.read(reinterpret_cast<char*>(&size), sizeof(size));
			string buffer;
			buffer.resize(size);
			fin.read(&buffer[0], buffer.size());
			print(buffer);
			//StringOfSymbols.push_back(buffer);
		}

		return (bool)fin;
	};

	void print(string buffer) {

		cout << buffer << endl;

		/*list <string> ::iterator it;
		for (it = StringOfSymbols.begin(); it != StringOfSymbols.end(); ++it) {
			cout << *it << endl;
		}*/
	};

	list<string> getList() {
		return StringOfSymbols;
	};
};

void WriteReadFile() {
	ofstream fout1;
	ifstream fin1;
	FileParser fileParser0;
	string fileName;

	cout << "Input file name (Example: f1.bin):" << endl;
	cin >> fileName;

	cout << "Input strings (ctrl+z to stop): " << endl;
	while (!cin.eof())
	{
		fileParser0.fillObject();
	};

	//write strings from input into file
	fout1.open(fileName, ios::binary);
	fileParser0.write(fout1);
	fout1.close();

	cout << "File contains:" << endl;
	//read and print strings from file
	fin1.open(fileName, ios::binary);
	fileParser0.read(fin1);
	fin1.close();
}

int main()
{	
WriteReadFile();		
}


/*
*													Test
* 
* Input in f1.bin	|	Output from f1.bin	 |	Input in f2.bin	 |	Output from f2.bin	 |	Output from f3.bin
*		emma					benj				 max				  drew						benj
*		drew					drew				 felix				  felix						drew
*		benj					emma				 drew				  max						emma
*																									felix
*																									max
*/