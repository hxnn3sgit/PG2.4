#include <iostream>
#include <fstream>
#include <vector>

using std::cout, std::endl, std::string;

void concatenate(std::istream &in, const std::vector<string> &args, bool line_flag = false) {
	
}

void concatenate(std::istream &in) {
	string line;
	while (std::getline(in, line))
		cout << line << endl;
}

void concatenate(std::istream &in, bool line_flag) {
	string line;
	if (line_flag) {
		int line_nr = 1;
		while (std::getline(in, line)) {
			cout << "\t " << line_nr++ << "  "  << line << endl;
		}
	} else {
		while(std::getline(in, line)) 
			cout << line << endl;
	}	
}

bool check_for_line_flag(const std::vector<string> &args) {
	for (const auto &arg : args) {
		if (arg == "-n")
			return true;
	}
	return false;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		concatenate(std::cin, true);	
	} else {
		std::vector<string> args;
		for (int i = 0; i < argc; ++i)
			args.push_back(argv[i]);
		
		bool line_flag = check_for_line_flag(args);

	}
	
	return 0;
}
