/*
 * PG2 Klausuraufgabe: Datenverarbeitung mit Streams, Exceptions und STL
 * 
 * Aufgabenstellung:
 * ================
 * 
 * Sie sollen ein System zur Verwaltung von Studentendaten implementieren.
 * Das System soll folgende Funktionalitäten bieten:
 * 
 * 1. Einlesen von Studentendaten aus einer CSV-Datei
 * 2. Speichern der Daten in geeigneten STL-Containern
 * 3. Verschiedene Auswertungen und Filterungen
 * 4. Robuste Fehlerbehandlung mit Exceptions
 * 5. Ausgabe der Ergebnisse in formatierter Form
 * 
 * Datenformat (CSV):
 * Matrikelnummer,Name,Studiengang,Semester,Note1,Note2,Note3
 * 123456,Mueller Max,Informatik,3,1.7,2.0,1.3
 * 234567,Schmidt Anna,Mathematik,5,2.3,1.0,2.7
 * 
 * Teilaufgaben:
 * =============
 * 
 * A) Implementieren Sie eine Klasse Student mit:
 *    - Alle notwendigen Datenfelder
 *    - Konstruktor, Destruktor, Copy-Konstruktor
 *    - Getter-Methoden
 *    - Methode zur Berechnung der Durchschnittsnote
 *    - Überladung der Operatoren << und >> für Stream-Ein/Ausgabe
 *    - Überladung des Operators < für Sortierung
 * 
 * B) Implementieren Sie eine Klasse StudentManager mit:
 *    - STL-Container zur Speicherung der Studenten
 *    - Methode loadFromFile(const string& filename)
 *    - Methode saveToFile(const string& filename) 
 *    - Methode findStudentsByProgram(const string& program)
 *    - Methode getTopStudents(int count)
 *    - Methode calculateAverageGrade()
 *    - Eigene Exception-Klassen für verschiedene Fehlertypen
 * 
 * C) Implementieren Sie eine main-Funktion, die:
 *    - Das System testet
 *    - Verschiedene Fehlerszenarien abfängt
 *    - Ergebnisse formatiert ausgibt
 * 
 * Bewertungskriterien:
 * - Korrekte Verwendung von STL-Containern (20 Punkte)
 * - Robuste Stream-Verarbeitung (15 Punkte)  
 * - Sinnvolle Exception-Behandlung (15 Punkte)
 * - Code-Qualität und Stil (10 Punkte)
 * - Funktionalität und Testen (15 Punkte)
 * - Bonus: Zusätzliche Features (5 Punkte)
 * 
 * Gesamt: 80 Punkte (+ 5 Bonus)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <exception>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// TODO: Implementieren Sie hier Ihre Lösung

// Eigene Exception-Klassen
class FileException : public exception {
private:
    string message;
public:
    FileException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class DataException : public exception {
private:
    string message;
public:
    DataException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class NoStudentInCourse : public exception {
private:
	std::string message;
public:
	NoStudentInCourse(const string &msg) : message(msg) {}
	const char* what() const noexcept override {
		return message.c_str();
	}

};

// A) Student-Klasse
class Student {
private:
		std::string MatrikelNr;
		std::string Name;
		std::string Kurs;
		int Semester;
		std::vector<float> Noten;
public:
	Student() = default;
	Student(const std::string &matrikel_nr, const std::string &name, const std::string &kurs, const int semester, const std::vector<float> &noten) : MatrikelNr(matrikel_nr), Name(name), Kurs(kurs), Semester(semester), Noten(noten) {}
	// dtor copy und move fehlt, ebenso assignment ops
	~Student() = default; // kein speicher allokiert in ctor, deswegen passt compiler dtor
	Student(const Student& other) = default;
	Student(Student &&other) = default;
    Student& operator=(const Student &other) = default;
	Student& operator=(Student &&other) = default;
	std::string get_MatrikelNr() const { return MatrikelNr; }
	std::string get_Name() const { return Name; }
	std::string get_Kurs() const { return Kurs; }
	int get_Semester() const { return Semester; }
	std::vector<float> get_Noten() const { return Noten; }
    
	float calculateAverageGrade() const {
		float sum = 0.0;
		for (const auto &note : Noten)
			sum += note;

		return sum / Noten.size();
	}
    
	friend std::ostream& operator<<(std::ostream& out, const Student &other) {
		out << "MatrikelNr/Name/Kurs/Semester:\n";
		out << other.MatrikelNr << ", " << other.Name << ", " << other.Kurs << ", " << other.Semester << std::endl;
		out << "Noten:\n";
		for (const auto &note : other.Noten)
			out << note << std::endl;

		return out;
	}

	friend std::istream& operator>>(std::istream &in, Student &other) {
			std::vector<std::string> student_tokens;	
			std::string line;

			if (std::getline(in, line)) {
                std::istringstream iss(line);
                std::string student_token;
                while (std::getline(iss, student_token, ','))
                    student_tokens.push_back(student_token);

				if (student_tokens.size() < 7)
					throw DataException("not enough data was read in");

				other.MatrikelNr = student_tokens.at(0);
				other.Name = student_tokens.at(1);
				other.Kurs = student_tokens.at(2);
				std::cout << "[LOGGER]: reading from file: " << other.Name << std::endl;
				try {
					other.Semester = std::stoi(student_tokens.at(3));
				} catch (std::invalid_argument &e) {
					std::cerr << "semester was not a number, nan is set instead: " << e.what() << std::endl;
					other.Semester = std::numeric_limits<int>::quiet_NaN();
				} catch (std::out_of_range &e) {
					std::cerr << "converted semester nubmer is invalid, nan is set instead: " << e.what() << std::endl;
					other.Semester = std::numeric_limits<int>::quiet_NaN();
				}
				other.Noten.clear();
				for (int i = 4; i < student_tokens.size(); ++i) {
					try {
						float current_grade = std::stof(student_tokens[i]);
						other.Noten.push_back(current_grade);
					} catch (std::invalid_argument &e) {
						std::cerr << "grade could not be converted and is set to nan istead : " << e.what() << std::endl;
						other.Noten.push_back(std::numeric_limits<float>::quiet_NaN());
					} catch (std::out_of_range &e) {
						std::cerr << "grade could not be converted and is set to nan instead: " << e.what() << std::endl;
						other.Noten.push_back(std::numeric_limits<float>::quiet_NaN());
					}
				}

            } else {
                in.setstate(std::ios::failbit);
            }

		return in;
	}
    
	bool operator<(Student &other) const { // ??? sollte const sein
		return (this->calculateAverageGrade() < other.calculateAverageGrade());
	}
	
};

// B) StudentManager-Klasse  
class StudentManager {
private:
    std::vector<Student> my_students; 
public:
	StudentManager() = default;
	StudentManager(const StudentManager& other) = default;
	StudentManager(StudentManager &&other) = default;
	StudentManager& operator=(const StudentManager &other) = default;
	StudentManager& operator=(StudentManager &&other) = default;

	void loadFromFile(const std::string& filename) {
		std::ifstream fin(filename);
		if (fin.is_open()) {
			Student my_student;
			while(fin >> my_student) {
				my_students.push_back(my_student);
			}	
		} else {
			throw FileException("file could not be opened!");
		}
	}
    
    // TODO: Implementieren Sie saveToFile()
    void saveToFile(const std::string& filename) const {
		std::ofstream fout(filename);
		if (fout.is_open()) {
			for(const auto &student : my_students)
				fout << student << std::endl;
		} else {
			throw FileException("file could not be opened!");
		}
	}

    // TODO: Implementieren Sie findStudentsByProgram()
	std::vector<Student> findStudentsByProgram(const std::string& program_name) const {
		std::vector<Student> same_program;
		for (const auto &student : my_students) {
			if (student.get_Kurs() == program_name)
				same_program.push_back(student);
		}

		if (same_program.empty())
			throw NoStudentInCourse("Keine Studenten in Kurs " + program_name);

		return same_program;
	}
    
	std::vector<Student> getTopStudents(int n = 3) const {
		if (n > my_students.size())
			throw std::logic_error("cant get top " + std::to_string(n) + " students, array is only of size" + std::to_string(my_students.size()));
		std::vector<Student> top_students = my_students;

		std::sort(top_students.begin(), top_students.end());

		std::vector<Student> top_n_students;
		for(int i = 0; i < n; ++i)
			top_n_students.push_back(top_students[i]);

		return top_n_students;
	}

    float calculateAverageGrade() {
		float avg_grade = 0.0;

		for (const auto &student : my_students) {
			avg_grade += student.calculateAverageGrade();
		}

		return (avg_grade / my_students.size());
	}

	friend std::ostream& operator<<(std::ostream& out, const StudentManager &other) {
		out << "STUDENT MANAGER\n";

		for (const auto &student : other.my_students) {
			out << student;
		}

		return out;
	}
};

// C) Main-Funktion
int main() {
    try {
        // TODO: Testen Sie Ihr System hier

		// TODO: Implementieren Sie verschiedene Testszenarien

        cout << "=== Studentenverwaltung Test ===" << endl;

		StudentManager my_manager;
		my_manager.loadFromFile("studenten.csv");
		std::cout << my_manager << std::endl;

		std::cout << "avg_grade: " << my_manager.calculateAverageGrade() << std::endl;

		std::cout << "=== dies studenten belegen mathe:\n";
		std::vector<Student> same_course_students = my_manager.findStudentsByProgram("Mathematik");
        
		for (const auto &same_course_student : same_course_students)
			std::cout << same_course_student << std::endl;

		std::cout << "=== das sind die top 3 studenten ===\n";

		std::vector<Student> top_3_students = my_manager.getTopStudents(3);

		for (const auto &student : top_3_students) 
			std::cout << student << std::endl;

		//my_manager.saveToFile("test.txt");

    } catch (const FileException& e) {
        cerr << "Datei-Fehler: " << e.what() << endl;
        return 1;
    } catch (const DataException& e) {
        cerr << "Daten-Fehler: " << e.what() << endl;
        return 1;
    } catch (const NoStudentInCourse &e) {
		std::cerr << "Kurs nicht belegt: " << e.what() << std::endl;
		return EXIT_FAILURE;
	} catch(const std::logic_error &e) {
		std::cerr << "unlogische anfrage: " << e.what() << std::endl;
		return EXIT_FAILURE;	
	} catch (const exception& e) {
        cerr << "Unerwarteter Fehler: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}

/*
 * Zusatzaufgaben (Bonus):
 * =======================
 * 
 * 1. Implementieren Sie eine Template-Funktion, die für beliebige Container
 *    mit Student-Objekten Statistiken berechnet
 * 
 * 2. Verwenden Sie Lambda-Ausdrücke für Filteroperationen
 * 
 * 3. Implementieren Sie Iterator-basierte Funktionen
 * 
 * 4. Nutzen Sie Smart Pointers wo sinnvoll
 * 
 * 5. Implementieren Sie eine Thread-sichere Version des StudentManagers
 */
