#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

using std::cout, std::endl, std::string;

class division_by_zero : public std::exception {
public:
	virtual const char *what() const noexcept override {
		return "Division by zero"; 
	}
};

struct Employee {
	std::string name;
	string abteilung;
	float gehalt;

	bool is_valid();
};

std::map<string, float> calc_avg_salary_by_department(const std::vector<Employee> &employees) {
	std::map<string, float> sum_salary_by_department;
	std::map<string, int> department_counter;

	for (const auto &employee : employees) {
		sum_salary_by_department[employee.abteilung] += employee.gehalt;
		department_counter[employee.abteilung] += 1;
	}

	std::map<string, float> avg_salary_by_department;
	
	for (const auto &pair : sum_salary_by_department) {

		avg_salary_by_department[pair.first] = sum_salary_by_department[pair.first] / department_counter[pair.first];
	}

	return avg_salary_by_department;
}

void process_employee_data(std::istream &in, std::vector<Employee> &employees) {
	// skip headline:
	string line; // for buffer
	std::getline(in, line); // skips first line
	while(std::getline(in, line)) { // iterates over line
		std::stringstream ss(line);

		Employee my_employee;
		string gehalt_token;
		string name_token;
	
		
		std::getline(ss, name_token, ';'); // stores name
		if (name_token.empty()) { // proper name verifycation
			my_employee.name = "INVALID_NAME";
			std::cerr << "no name provided, INVALID_NAME is set" << endl;
		} else {
			my_employee.name = name_token;
		}
		std::getline(ss, my_employee.abteilung, ';'); // stores department
		std::getline(ss, gehalt_token, ';');

		// try to convert string float value in float value:
		try {
			float loan = std::stof(gehalt_token);
			my_employee.gehalt = loan;
		} catch (std::invalid_argument &e) {
			my_employee.gehalt = std::numeric_limits<float>::quiet_NaN();
			std::cerr << "invalid float value: " << e.what() << ", 'gehalt' is set to NaN" << endl;
		}
	
	employees.push_back(my_employee);
	}
}

void write_employee_data_in_file(std::ostream &out, const std::map<string, float> &avg_salary_by_department) {
	for (const auto &pair : avg_salary_by_department)
		out << pair.first << " has average loan of " << pair.second << endl;
}

int main() {
	string filename = "employees.csv";

	std::ifstream read_file(filename);
	
	std::vector<Employee> employees;
	process_employee_data(read_file, employees);
	read_file.close(); // not needed anymore
	
	std::map<string, float> avg_salarys_by_department = calc_avg_salary_by_department(employees);
	cout << endl;
	
	// iterate over map and print everything
	for (const auto &pair : avg_salarys_by_department) {
		cout << "[" << pair.first << "] = " << pair.second << endl;
	}

	try {
		std::ofstream avg_salary_file("avg_salaries_by_department.txt");
		write_employee_data_in_file(avg_salary_file, avg_salarys_by_department);
		avg_salary_file.close();
	} catch (std::exception &e) {
		std::cerr << "writing to file failed: " << e.what() << endl;
	}
	
	return 0;
}
