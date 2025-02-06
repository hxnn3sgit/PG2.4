#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printFileContentWithLines(int argc, char **argv) {
	// going with for loop through argv
	// open every file and print file content on command line with line number n = i+1
	int n = 1;
	for (int i = 1; i < argc; ++i) {
		string fileName = argv[i];
		ifstream myFile;
		myFile.open(fileName);
		if (!myFile.is_open()) {
			cerr << "could not open file. exit program..." << endl;
			exit(-1);
		}
		string buffer;
		while (getline(myFile, buffer))
			cout << n++ << "\t" << buffer << endl;
		myFile.close();
	}
}

void printFileContentWithoutLines(int argc, char **argv) {
	for (int i = 1; i < argc; ++i) {
		string fileName = argv[i];
		ifstream myFile;
		myFile.open(fileName);
		if (!myFile.is_open()) {
			cerr << "could not open file. exit program..." << endl;
			exit(-1);
		}
		string buffer;
		while (getline(myFile, buffer))
			cout << buffer << endl;
		myFile.close();
	}	
}

int main(int argc, char **argv) {
	if (argc < 2) {
		cerr << "no filename. Exit program..." << endl;
		return -1;
	}
	
	bool lineNumber = false;

	for (int i = 1; i < argc; ++i) {
		string temp = argv[i];
		if (temp == "-n") lineNumber = true;
	}

	if (lineNumber == true)
		printFileContentWithLines(argc, argv);
	else
		printFileContentWithoutLines(argc, argv);

}
