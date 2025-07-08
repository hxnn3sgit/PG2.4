#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <exception>

class delete_not_succeeded : public std::exception {
private:
	std::string message;
public:
	delete_not_succeeded(const std::string &msg) : message(msg) {}
	virtual const char* what() const noexcept {
		return message.c_str();
	}
};

struct Student {
    std::string name;
    int semester;
    double gpa;
    
    Student(const std::string& n, int sem, double g) 
        : name(n), semester(sem), gpa(g) {}

	friend std::ostream& operator<<(std::ostream& out, const Student &other) {
		out << other.name << ", " << other.semester << ", " << other.gpa;
		
		return out;
	}
};

class StudentManager {
private:
    std::map<int, Student> students_by_id;           // sortiert nach ID
    std::unordered_map<std::string, int> name_to_id; // schneller Zugriff
    int next_id = 1000;

public:

	std::map<int, Student> getStudentMap()const { return students_by_id; }
    // TODO: Implementieren Sie folgende Methoden:
    
    // 1. Student hinzufügen (2 Punkte)
    int addStudent(const std::string& name, int semester, double gpa);
    
    // 2. Student finden (2 Punkte) 
    Student* findStudent(int id);
    Student* findStudentByName(const std::string& name);
    
    // 3. Student entfernen (2 Punkte)
    bool removeStudent(int id);
    
    // 4. Alle Studenten ausgeben (2 Punkte)
    void printAllStudents() const;
    
    // 5. Statistiken (2 Punkte)
    size_t getStudentCount() const;
    double getAverageGPA() const;

	void printStudentsInRange(int min_id, int max_id);
	void removeStudentsWithLowGPA(double threshold);
};

int StudentManager::addStudent(const std::string &name, int semester, double gpa) {
	students_by_id.emplace(next_id, Student(name, semester, gpa));
	name_to_id.emplace(std::make_pair(name, next_id));
	return next_id++;
}

Student* StudentManager::findStudent(int id) {
	// ohne auto:
	auto search = students_by_id.find(id);
	if (search != students_by_id.end())
		return &search->second;
	else
		return nullptr;
}

bool StudentManager::removeStudent(int id) {
	Student* student_to_erase = findStudent(id);
	if (student_to_erase == nullptr) {
		throw delete_not_succeeded("tried to delete a student with id " + std::to_string(id) + ", id doesn't exist");
	}
	std::string student_to_erase_name = student_to_erase->name;
	if (students_by_id.erase(id) && name_to_id.erase(student_to_erase_name))
		return true;
	else
		return false;
}

void StudentManager::printAllStudents() const {
	for (const auto& [key, value] : students_by_id) {
		std::cout << key << ", " << value.name << ", " << value.semester << ", " << value.gpa << std::endl;
	}
}

size_t StudentManager::getStudentCount() const { return students_by_id.size(); }

double StudentManager::getAverageGPA() const {
	double avg = 0.0;

	for (const auto &[key, value] : students_by_id) {
		avg += value.gpa;
	}

	size_t num_of_students = getStudentCount();
	return avg / num_of_students;
}

__attribute__((noinline))
Student* StudentManager::findStudentByName(const std::string &name) {
	// auf normaler std::map:
	/*
	for (auto &[key, value] : students_by_id) {
		if (value.name == name) {
			return &value;
		}
	}
	return nullptr; */

	// std::unordered_map:
	auto search = name_to_id.find(name);
		if (search != name_to_id.end()) {
		int student_id = search->second;
		return &students_by_id.at(student_id);
	} else
		return nullptr;
}

// 6. Custom Comparator für std::map (3 Punkte)
// Sortierung nach GPA (höchste zuerst), dann nach Name
struct GPAComparator {
    // TODO: Implementieren Sie operator()
	bool operator()(const Student &a, const Student&b) const {
		if (a.gpa != b.gpa) {
			return a.gpa < b.gpa;
		} else {
			return a.name < b.name;
		}
	}
};

class AdvancedStudentManager {
private:
    std::map<Student, int, GPAComparator> students_by_gpa;
    
public:
    // TODO: Implementieren Sie:
    void importFrom(const StudentManager &mgr);
    // 7. Range-basierte Operationen (2 Punkte)
    std::vector<Student> getTopStudents(int count);
    std::vector<Student> getStudentsBySemester(int semester);


    // 8. Map-Algorithmen verwenden (3 Punkte)
    void updateAllGPAs(double bonus);
    std::map<int, int> getSemesterDistribution();
};

void AdvancedStudentManager::importFrom(const StudentManager &mgr) {
	auto studentManagerMap = mgr.getStudentMap();
	for (const auto& [key, value] : studentManagerMap) {
		students_by_gpa.insert(std::make_pair(value, key)); 
	}	 
}

std::vector<Student> AdvancedStudentManager::getTopStudents(int count) {
	assert(count < students_by_gpa.size());
	std::vector<Student> top_students;
	
	int top_student_count = 0;

	for (auto &[student, value] : students_by_gpa) {
		if (top_student_count < count) {
			top_students.push_back(student);
			top_student_count++;
		}
		else
			break;
	}

	return top_students;

}

 // 9. Iterator-Operationen (4 Punkte)
void StudentManager::printStudentsInRange(int min_id, int max_id) {
    // TODO: Verwenden Sie lower_bound und upper_bound
	auto lower_bound = students_by_id.lower_bound(min_id);
	auto upper_bound = students_by_id.upper_bound(max_id);

	for (std::map<int, Student>::iterator it = lower_bound; it != upper_bound; ++it)
		std::cout << it->second << std::endl;
}

void StudentManager::removeStudentsWithLowGPA(double threshold) {
    // TODO: Sicheres Entfernen während Iteration
	for (auto it = students_by_id.begin(); it != students_by_id.end();) {
		if (it->second.gpa < threshold) {
			// delete
			std::string name_of_to_delete_student = it->second.name;
			it = students_by_id.erase(it); // deleted from original map and ensured it does not go off
			name_to_id.erase(name_of_to_delete_student);
		} else {
			++it;
		}
	}
	
}

// 10. Performance-Vergleich (3 Punkte)
void performanceTest(int n = 10000) {
    // TODO: Implementieren Sie einen Test, der zeigt:
    // - Einfügen von 10000 Elementen in map vs unordered_map
    // - Suchen nach Elementen in beiden Containern
    // - Messen Sie die Zeit mit std::chrono

	StudentManager my_mgr;
	std::vector<int> student_ids;
	student_ids.reserve(n);
	 
	for (int i = 0; i < n; ++i) {
		Student my_student("test", 3, 3.3);
		int current_student_id = my_mgr.addStudent("test", 2, 3.3);
		student_ids.push_back(current_student_id);
	}


}

int main() {

	StudentManager my_student_manager;
	int first_add = my_student_manager.addStudent("Hannes", 6, 2.56);
	int second_add = my_student_manager.addStudent("Test", 2, 1.2);
	int third_add = my_student_manager.addStudent("dritte", 3, 3.3);
	int fourth_add = my_student_manager.addStudent("vierte", 4, 4.3);
	my_student_manager.printAllStudents();
	/*
	try {
		my_student_manager.removeStudent(232);
	} catch (delete_not_succeeded &e) {
		std::cerr << "exception occured during remove: " << e.what() << std::endl;
		return 1;
	}*/

	Student *my_student = my_student_manager.findStudent(first_add);
	
	std::cout << "mein student: " << *my_student << std::endl;

	std::cout << "avg student gpa: " << my_student_manager.getAverageGPA() << std::endl;

	Student *hannes_student;
   	hannes_student = my_student_manager.findStudentByName("Hannes");
	if (hannes_student != nullptr)
		std::cout << "hannes student: " << *hannes_student << std::endl;
	else
		std::cerr << "student not found\n";


	AdvancedStudentManager my_adv_student_mgr;
	my_adv_student_mgr.importFrom(my_student_manager);

	std::vector<Student> top_students = my_adv_student_mgr.getTopStudents(2);
	std::cout << "\ntop students:\n";
	for (const auto &x : top_students)
		std::cout << x << std::endl;

	std::cout << "\nprint students in range 1000; 1002\n";
	my_student_manager.printStudentsInRange(1000,1002);

	std::cout << std::endl << std::endl << "delete students below certain treshold of: " << 2.7 << std::endl;
	my_student_manager.removeStudentsWithLowGPA(2.7);

	my_student_manager.printAllStudents();

	performanceTest();

	return 0;
}
