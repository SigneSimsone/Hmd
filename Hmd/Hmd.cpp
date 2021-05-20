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

		StringOfSymbols.push_back(InputString);
		StringOfSymbols.sort();
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
		if (StringOfSymbols.size() > 0) {
			StringOfSymbols.clear();
		}

		unsigned int size = 0;

		while (!fin.eof()) {
			fin.read(reinterpret_cast<char*>(&size), sizeof(size));
			string buffer;
			buffer.resize(size);
			fin.read(&buffer[0], buffer.size());

			StringOfSymbols.push_back(buffer);
		}

		return (bool)fin;
	};

	void print() {
		cout << "File contains:" << endl;
		list <string> ::iterator it;
		for (it = StringOfSymbols.begin(); it != StringOfSymbols.end(); ++it) {
			cout << *it << endl;
		}
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

	//read and print strings from file
	fin1.open(fileName, ios::binary);
	fileParser0.read(fin1);
	fileParser0.print();
	fin1.close();
}

void ProcessExistingFiles() {
	ifstream fin1;
	ifstream fin2;
	ifstream fin3;
	ofstream fout3;
	string fileName[2];

	FileParser fileParserFile1;
	FileParser fileParserFile2;
	FileParser fileParserFile3;

	list<string> combinedList;
	list<string> list1;
	list<string> list2;

	cout << "Input both file names (Example: f1.bin):" << endl;
	for (int i = 0; i < 2; i++) {
		cin >> fileName[i];
	}

	//read the first file into a list
	fin1.open(fileName[0], ios::binary);
	fileParserFile1.read(fin1);
	list1 = fileParserFile1.getList();
	fin1.close();

	//read the second file into a list
	fin2.open(fileName[1], ios::binary);
	fileParserFile2.read(fin2);
	list2 = fileParserFile2.getList();
	fin2.close();

	//merge both lists together
	list <string> ::iterator it;
	for (it = list2.begin(); it != list2.end(); ++it) {
		list1.push_back(*it);
	}

	//sort the list and delete duplicates
	list1.sort();
	list1.unique();


	//write the list into a new file
	fileParserFile3.fillObjectForMergedFiles(list1);
	fout3.open("f3.bin", ios::binary);
	fileParserFile3.write(fout3);
	fout3.close();


	fin3.open("f3.bin", ios::binary);
	fileParserFile3.read(fin3);
	fileParserFile3.print();
	fin3.close();
}

int main()
{
	int userChoice;

	cout << "Press 1 to create new input files or press 2 to process existing input files" << endl;
	cin >> userChoice;

	switch (userChoice) {
	case 1:
		WriteReadFile();
		break;
	case 2:
		ProcessExistingFiles();
		break;
	}
};


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