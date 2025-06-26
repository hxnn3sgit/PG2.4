#include <iostream>
#include <string>

template<typename T>
struct Printer {
    void print(const T& value) {
        std::cout << "Generic printer: " << value << std::endl;
    }
};

// 1. Vollspezialisierung für std::string
// (hier fehlt etwas)
template<>
struct Printer<std::string> { // komplett ohne templates
	void print(const std::string& value) {
		std::cout << "string printer: " << value << std::endl;
	}
};

// 2. Partielle Spezialisierung für Pointer-Typen
// (hier fehlt etwas)

template<typename T>
struct Printer<T*> {
	void print(const T* value) {
		if (value)
			std::cout << "T* printer: " << *value << std::endl;
		else
			std::cout << "nullpointer!" << std::endl;
	}
};

int main() {
    Printer<int> p1;
    Printer<std::string> p2;
    Printer<double*> p3;

    int a = 5;
    std::string s = "hello";
	double d = 3.14;
    double *d_ptr = &d;

    p1.print(a);      // (A)
    p2.print(s);      // (B)
    p3.print(&d);     // (C)

    return 0;
}

