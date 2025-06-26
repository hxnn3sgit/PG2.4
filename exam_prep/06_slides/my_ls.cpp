#include <iostream>
#include <filesystem>
#include <exception>
#include <string>
#include <regex>

namespace fs = std::filesystem;

void print_current_dir(bool a_flag = false) {
	// get current dir
	// iterate through it and print each file:
		fs::path current_p = fs::current_path();
		
	
		if (a_flag) {
		for (const auto &entry : fs::directory_iterator(current_p))
			std::cout << entry.path().filename() << "  ";
		std::cout << "\n";
		} else {
			std::cout << "print files without swp" << std::endl;
		}
}

int main(int argc, char **argv) {
	try {	
		if (argc == 1) {
			print_current_dir();	
		} else if (argc == 2) {
			std::string a_flag = argv[1];
			if (a_flag == "-a")	
				print_current_dir(true);
			else
				throw std::runtime_error("invalid option for ls");
		}
	} catch (const fs::filesystem_error &e) {
		std::cerr << "exception occured: " << e.what() << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << "exception occured: " << e.what() << std::endl;
	}
	return 0;
}
