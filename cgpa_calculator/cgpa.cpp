#include "cgpa.h"
#include <iostream>
#include <vector>

using std::cout, std::endl, std::cin;

void execute_cgpa() {
    //do the stuff
    std::cout << "Hello from 'execute_cgpa' " << std::endl;
    int course_numbers = get_course_number();
    std::vector<float> grades;
    get_grades(grades);
    get_credit_points();
}

int get_course_number() {
    cout << "Type in how much courses you had: ";
    int course_no = 0;
    cin >> course_no;
    cout << endl;
    return course_no;
}

void get_grades(std::vector<float> grades) {
    cout << "type in your grades:" << endl;
    float temp;
    while (cin >> temp) {
        grades.push_back(temp);
    }
}

void get_credit_points() {
    //vllt mit std::map oder anderen strukturen.
}