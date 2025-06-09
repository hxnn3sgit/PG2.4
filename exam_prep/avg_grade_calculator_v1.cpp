#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

struct student {
	std::string last_name;
	std::vector<float> grades;

	float calc_grade_avg() const {
		if (!grades.empty()) {
			float grade_sum = 0.0;
	
			for (const auto &grade : grades) {
				grade_sum += grade;
			}

			return grade_sum / grades.size();
		} else {
			throw std::runtime_error("Division by zero!");
		}
	}
};

void handle_notes_file(const std::string &filename) {
	std::fstream file(filename);
	if (!file) {
		std::cerr << "File with name '" << filename << "' couldn't be openend" << std::endl;
		return;
	}
	
	std::string buffer;
	std::vector<student> students;
	std::getline(file, buffer); // skip first line; \n is split symbol
	
	while(std::getline(file, buffer)) {
		std::stringstream ss(buffer);
		std::string name;
			
		student my_student;

		std::getline(ss, name, ';');

		my_student.last_name = name;
		std::string temp;
		std::vector<float> grades;
		float grade_avg = 0.0;

		while(std::getline(ss, temp, ';')) {
			try {
				float value = std::stof(temp);
				my_student.grades.push_back(value);
				} catch (const std::exception &e) {
					std::cerr << "unvalid float value, skipping item: " << temp << std::endl;
					continue;
			}
		}

		students.push_back(my_student);
	}
	std::ofstream ofstream_file;
	ofstream_file.open("avg_grades", std::ios::app);
	for (const auto &student : students) {
		std::cout << student.last_name << " has average grade of " << student.calc_grade_avg() << std::endl;
		ofstream_file << student.last_name << " has average grade of " << student.calc_grade_avg() << std::endl;
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
