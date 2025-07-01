#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <filesystem>
#include <sstream>

#include "../../../my_own_librarys/dyn_arr/dyn_arr.h"

namespace fs = std::filesystem;

void fold(std::istream &in) {
	char c;
	while (in.get(c)) {
			if (isalnum(c))
				std::cout << c;
			else
				std::cout << '\n';
	}
}


int main(int argc, char **argv) {
	if (argc == 1) {
		fold(std::cin);
	} else {
		for (int i = 1; i < argc; ++i) {
			try {
				fs::path file_path = argv[i];
				if (!fs::exists(file_path))
					throw std::runtime_error("file coulnt't be opened");
				std::ifstream fin(file_path);
				fold(fin);
			} catch (std::exception &e) {
				std::cerr << "exception occured: " << e.what() << std::endl;
			}
		}
	}

	return 0;
}
