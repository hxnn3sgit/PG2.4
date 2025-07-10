#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <exception>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;

class parse_error : public std::exception {
public:
	virtual const char* what() const noexcept override {
		return "error while parsing student, either name or grade wrong format";
	}
};	

struct Student {
	std::string Name;
	int Note;
	Student() = default;
	Student(const std::string &n, const int g) : Name(n), Note(g) {}
};

bool is_valid_word(const std::string &name_to_check) {
	for (int i = 0; i < name_to_check.length(); ++i) { 
		if (!isalpha(name_to_check[i]) && !isspace(name_to_check[i])) {
			return false;
		}	
	}
	return true;
}

/*
Student parse_and_create_student(const std::string &student_line) {
	std::string student_name;
	int student_grade;
	std::istringstream iss(student_line);
	std::getline(iss, student_name, ',');
	if (is_valid_word(student_name) && (iss >> student_grade)) {
		return Student(student_name, student_grade);
	} else
		throw parse_error();
}
*/

// new regex version:
Student parse_and_create_student(const std::string &student_line) {
	std::regex pattern{R"(^[a-zA-Z]+(\s+[a-zA-Z]+)?,(100|[1-9][0-9]?|0)\s*$)"};
	std::smatch match;
	if (std::regex_match(student_line, match, pattern)) {
		std::string valid_line = match.str();
		std::istringstream iss(valid_line);
		std::string student_name;
		int student_grade;
		if ((std::getline(iss, student_name, ',') && (iss >> student_grade))) {
			return Student(student_name, student_grade);
		}
	}

	throw parse_error();
}

float student_grade_avg(const std::vector<Student> &students) {
	if (students.size() != 0) {
		float avg = 0.0;
		for (const auto &student : students) {
			avg += student.Note;
		}

		return (avg / students.size());
	} else {
		throw std::logic_error("vector has size zero");
	}
}

int main() {
	std::cout << "Geben Sie bitte die Datei der Studenten an: ";
	fs::path p;
	std::cin >> p;

	if (!fs::exists(p)) {
		std::cerr << "Datei existiert nicht!\n";
		return 1;
	}

	std::ifstream fin(p);

	if (!fin.is_open()) {
		std::cerr << "Datei konnte nicht geöffnet werden\n";
		return 1;
	}

	std::vector<Student> students;
	std::string file_line;
	int line_count = 1;
	
	while(std::getline(fin, file_line)) {
		line_count++;
		try {
			students.push_back(parse_and_create_student(file_line));
		} catch (parse_error &e) {
			std::cerr << "exception in line " << line_count << " occured: " << e.what() << std::endl;
			continue;
		}
	}

	try {
		std::cout << "grade avg among students: " << student_grade_avg(students) << std::endl;
	} catch (std::logic_error &e) {
		std::cerr << "exception when calculating avg grade occured: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
