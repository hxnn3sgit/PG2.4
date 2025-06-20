#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct student {
	std::string last_name;
	std::vector<float> grades;
};

float calc_grade_avg(const std::vector<float> grades) {
	if (!grades.empty()) {
		float grade_sum = 0.0;
	
		for (const auto &grade : grades) {
			grade_sum += grade;
		}

		return grade_sum / grades.size();
	} else {
		std::cerr << "Divison by zero!" << std::endl;
		return -1;
	}
}

void handle_notes_file(const std::string &filename) {
	std::fstream file(filename);
	if (!file) {
		std::cerr << "File with name '" << filename << "' couldn't be openend" << std::endl;
		exit(-1);
	}
	
	std::string buffer;

	std::getline(file, buffer); // skip first line; \n is split symbol
	while(std::getline(file, buffer)) {
		std::stringstream ss(buffer);
		std::string name;
		std::getline(ss, name, ';');
		std::string temp;
		std::vector<float> grades;
		float grade_avg = 0.0;

		while(std::getline(ss, temp, ';')) {
			try {
				float value = std::stof(temp);
				grades.push_back(value);
				} catch (const std::exception &e) {
					std::cerr << "unvalid float value, skipping item: " << temp << std::endl;
					continue;
			}
		}
		grade_avg = calc_grade_avg(grades);	
		std::cout << name << " has avg_grade " << grade_avg << std::endl;
		std::fstream grades_file("avg_grades.txt");
		grades_file << grade_avg << " has avg_grade " << name << std::endl;
	} 
}

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "no filename provided. Please pass filename." << std::endl;
		return -1;
	}

	std::string filename = argv[1];
	handle_notes_file(filename);

	return 0;
}
