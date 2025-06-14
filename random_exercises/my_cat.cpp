#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <string>

using std::cout, std::endl, std::string;

class file_not_opened : public std::exception {
public:
	virtual const char *what() const noexcept override {
		return "file could not be opened";
	}			
};

void concatenate(std::istream &in, bool line_flag = false) {
	string line;
	if (line_flag) {
		int line_nr = 1;
		while (std::getline(in, line)) {
			cout << "  " << line_nr++ << "\t" << "  "  << line << endl;
		}
	} else {
		while(std::getline(in, line)) 
			cout << line << endl;
	}	
}

bool check_for_line_flag(std::vector<string> &args) {
	bool line_flag = false;
	for (int i = 0; i < args.size(); ++i) {
		if (args.at(i) == "-n"){
			args.erase(args.begin() + i);
			line_flag = true;
		}
	}
	return line_flag;
}

int main(int argc, char **argv) {
	if (argc == 1) { // reading over std::cin with no line-flag
		concatenate(std::cin, false);	
	} else if (argc == 2) { // reading over std::cin with line-flag
		string argv_2 = argv[1];
 		if (argv_2 == "-n")
			concatenate(std::cin, true);
		else { // read from file
			std::ifstream my_file;
			my_file.open(argv_2);
			if (!my_file.is_open()) {
				throw file_not_opened();
			} else {
				concatenate(my_file);
			}
		}
	} else if (argc > 1) { // reading from file
		std::vector<string> args;
		for (int i = 1; i < argc; ++i)
			args.push_back(argv[i]);
		
		bool line_flag = check_for_line_flag(args);
		
		for(const auto &arg : args) {
			try {
				std::ifstream my_file;
				my_file.open(arg);
				if (my_file.is_open()) {
					concatenate(my_file, line_flag);
				} else {
					throw file_not_opened();
				}
			} catch (file_not_opened &e) {
				std::cerr << "error while opening file: " << e.what() << endl;
			} catch (std::exception &e) {
				std::cerr << "exception occured: " << e.what() << endl;
			}
		}
	}
	
	return 0;
}
