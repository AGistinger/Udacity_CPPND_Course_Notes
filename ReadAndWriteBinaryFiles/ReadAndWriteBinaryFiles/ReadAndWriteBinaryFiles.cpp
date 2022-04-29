// ReadAndWriteBinaryFiles

/*
Read and Write Binary Files
-If you use fstream instead of ofstream you need to add ios::out to flag an outgoing file
-ofstream the default is ios::out
-Using binarys is very useful when saving and opening files for applications
-Different files may require research on how to read and write bytes for other file types
*/

#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push,1) //remove padding from struct
struct Person
{
	char name[50];
	int age;
	double height;
};
#pragma pack(pop)

int main()
{
	Person someone {"Frodo", 220, 0.8}; //Initialize struct
	
	string file_name {"test.bin"};  //.bin is a binary file

	ofstream output_file;
	output_file.open(file_name, ios::binary);  //Need to say ios::binary to declare use of a binary file (default is .txt)

	//Write Binary File////////
	if (output_file.is_open())
	{
		//(Old way) You can type cast a antoher type of pointer to a char * by putting (char *) in front of the object address
		//You also need to supply how much data (bytes) you want to write, sizeof(Person)
		//output_file.write((char *)&someone, sizeof(Person)); <<-- Old way
		//(New way) reinterpret_cast<type>(pointer)
		//output_file.write(reinterpret_cast<char *>(&someone), sizeof(Person));  <<-- New way
		output_file.write(reinterpret_cast<char *>(&someone), sizeof(Person));  //Create person pointer
		output_file.close();
	}
	else
	{
		cout << "Could not create file " << file_name << endl;
	}

	//Read Binary File/////////
	Person someone_two {};
	ifstream input_file;
	input_file.open(file_name, ios::binary);

	if (input_file.is_open())
	{
		input_file.read(reinterpret_cast<char *>(&someone_two), sizeof(Person));
		input_file.close();
	}
	else
	{
		cout << "Could not read file " << file_name << endl;
	}
	
	//Display the new object that the information was read into
	cout << someone_two.name << ", " << someone_two.age << ", " << someone_two.height << endl;

    return 0;
}