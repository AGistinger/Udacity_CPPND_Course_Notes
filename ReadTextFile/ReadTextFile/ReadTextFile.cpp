// ReadTextFile

/*
Reading from Text files
If you are using fstream instead of ifstream you can use in_file.open(file_name, ios::in) 
to tell the program you want to read from a file.

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	string file_name {"test.txt"};
	ifstream in_file;
	in_file.open(file_name);
	//in_file.open(file_name, ios::in);

	if (in_file.is_open())
	{
		string line;
		while(getline(in_file, line)) //while(!in_file.eof()) or while(in_file)
		{
			cout << line << endl;
		}
		in_file.close();
	}
	else
	{
		cout << "Cannot open file: " << file_name << endl;
	}



    return 0;
}