#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <map>
#include <vector>

using namespace std;

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

	/*for (const auto &pair */


	
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
			cerr << "invalid float value: " << e.what() << ", 'gehalt' is set to NaN" << endl;
		}
	
	employees.push_back(my_employee);
	}
}

int main() {
	string filename = "employees.csv";

	std::ifstream read_file(filename);
	
	std::vector<Employee> employees;
	process_employee_data(read_file, employees);

	for (const auto &employee : employees) {
		cout << employee.name << ", " << employee.abteilung << ", " << employee.gehalt << endl;
	}
	read_file.close(); // not needed anymore
	
	//std::map<string, float> avg_salarys_by_department = calc_avg_salary_by_department(employees);

	// iterate over map and print everything
	

	return 0;
}
