#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <Windows.h>

using namespace std;

std::string GetCurrentDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

string getNextString(istream& fin) {
	unsigned int size = 0;
	fin.read(reinterpret_cast<char*>(&size), sizeof(size));
	string buffer;
	buffer.resize(size);
	fin.read(&buffer[0], buffer.size());
	return buffer;
}

void writeStringToF3(std::string& buffer, std::ofstream& fout3)
{
	unsigned int size = buffer.size();
	fout3.write(reinterpret_cast<char*>(&size), sizeof(size));
	fout3.write(buffer.c_str(), size);
}

int getLineCount(string fileName, ifstream& fin) {
	fin.open(fileName, ios::binary);
	int count = 0;
	string line;
	while (getline(fin, line)) {
		count++;
	}
	fin.close();
	return count;
}

void read(string fileName[2]) {
	
	ifstream fin1;
	ifstream fin2;
	ofstream fout3;

	int lineCountF1 = getLineCount(fileName[0], fin1);
	int lineCountF2 = getLineCount(fileName[1], fin2);

	if (lineCountF1 < lineCountF2) {
		fin1.open(fileName[0], ios::binary);
		fin2.open(fileName[1], ios::binary);
	}
	else {
		fin1.open(fileName[1], ios::binary);
		fin2.open(fileName[0], ios::binary);
	}

	fout3.open("f3_temp.bin", ios::binary);

	while (!fin1.eof()) {

		string buffer1 = getNextString(fin1);
		//while (!fin2.eof()) {
			string buffer2 = getNextString(fin2);

			int result = buffer1.compare(buffer2);

			switch (result) {
			case 0:
				writeStringToF3(buffer1, fout3);
				break;
			case 1:
				writeStringToF3(buffer2, fout3);
				writeStringToF3(buffer1, fout3);
				break;
			case -1:
				writeStringToF3(buffer1, fout3);
				writeStringToF3(buffer2, fout3);
				break;
			}
		
	}
	fin1.close();
	fin2.close();
	fout3.close();
}

void removeDuplicatesFromF3() {
	ifstream fin3;
	ofstream fout3;
	fin3.open("f3_temp.bin", ios::binary);
	fout3.open("f3.bin", ios::binary);
	string lastValue = "";
	while (!fin3.eof()) {
		string buffer = getNextString(fin3);
		if (lastValue == "") {
			writeStringToF3(buffer, fout3);
			lastValue = buffer;
		}

		if (lastValue != buffer) {
			writeStringToF3(buffer, fout3);
		}
		lastValue = buffer;
	}
	fin3.close();
	fout3.close();
}

void print(string filename) {
	ifstream fin3;
	fin3.open(filename, ios::binary);
	unsigned int size = 0;
	while (!fin3.eof()) {
		fin3.read(reinterpret_cast<char*>(&size), sizeof(size));
		string buffer;
		buffer.resize(size);
		fin3.read(&buffer[0], buffer.size());
		cout << buffer << endl;
	}
	fin3.close();
}

int main()
{
	string path = GetCurrentDirectory() + "\\..\\Hmd\\";
	string fileName[2];

	cout << "Input both file names (Example: f1.bin):" << endl;
	for (int i = 0; i < 2; i++) {
		string temp;
		cin >> temp;
		fileName[i] = path + temp;
	}

	read(fileName);
	removeDuplicatesFromF3();
	print("f3.bin");
}

