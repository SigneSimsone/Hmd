//#include<iostream>
//#include<fstream>
//#include<string>
//using namespace std;
//
//void WriteToFile(ofstream& output, int& size, string& string)
//{
//	output.write(reinterpret_cast<char*>(&size), sizeof(int));
//	output.write(string.c_str(), size);
//}
//
//void ReadFile(ifstream& input, int& size, char*& buf, string& string)
//{
//	input.read(reinterpret_cast<char*>(&size), sizeof(int));
//	buf = new char[size];
//	input.read(buf, size);
//	cout << buf << endl;
//
//}
//
//int main() {
//
//	char* buf;
//
//	int Count;
//	int Size;
//
//	ofstream Output("f2.bin", ios::out | ios::binary);
//	if (!Output.is_open())
//	{
//		cout << "can't open file" << endl;
//		exit(1);
//	}
//
//	cout << "How many strings in file f2?" << endl;
//	cin >> Count;
//
//	string* StringOfSymbols = new string[Count];
//
//	cout << "Input strings:" << endl;
//	for (int i = 0; i < Count; i++) {
//		cin >> StringOfSymbols[i];
//		Size = StringOfSymbols[i].size();
//		WriteToFile(Output, Size, StringOfSymbols[i]);
//	}
//
//	Output.flush();
//	Output.close();
//
//
//	ifstream Input("f2.bin", ios::in | ios::binary);
//	if (!Output.is_open())
//	{
//		cout << "can't open file" << endl;
//		exit(1);
//	}
//
//	cout << endl;
//	cout << "File f2 contains:" << endl;
//	for (int i = 0; i < Count; i++) {
//		ReadFile(Input, Size, buf, StringOfSymbols[i]);
//	}
//
//	Input.close();
//
//	return 0;
//}