#include <iostream>
#include <vector>
#include <list>
#include <exception>
#include <string>
#include <sstream>

/*
class division_by_zero : public std::exception {
public:
	virtual const char *what() const noexcept override {
		return "Division by Zero!";
	}
};

float divide(const float a, const float b) {
	if (b == 0)
		throw division_by_zero();
	else return a / b;
}

int main() {
	std::string line;
	while (true) {
		std::getline(std::cin, line); 
		if (std::cin.eof())
			break;
		float a = 0.0;
		float b = 0.0;
		
		std::istringstream iss(line);
		std::string a_as_str;
		std::getline(iss, a_as_str, ' ');
		std::string b_as_str;
		std::getline(iss, b_as_str, ' ');

		try {
			a = std::stof(a_as_str);
			b = std::stof(b_as_str);
		} catch(std::invalid_argument &e) {
			std::cerr << "exception occured during stof: " << e.what() << std::endl;
			continue;
		}

		try {
			std::cout << a << " / " << b << " = " << divide(a, b) << std::endl;
		} catch (division_by_zero &e) {
			std::cerr << "exception occured during divison; " << e.what() << std::endl;
			continue;
		}
	}
	return 0;
}
*/

template<
	template<typename> class Container,
	typename T
>
T find_max(const Container<T> &my_container) {
	if (my_container.empty())
		throw std::logic_error("can't evaluate container of size zero!");
	else {
		T largest = my_container.at(0);
		auto it = my_container.begin();

		for (auto it = my_container.begin(); it != my_container.end(); ++it) {
			if (*it > largest)
				largest = *it;
		}

		return largest;
	}
} 
/*
template<typename Container>
typename Container::value_type find_max(const Container &my_container) {
	if (my_container.empty())
		throw std::invalid_argument("cannot search for max, container is empty");

	auto it = my_container.begin();
	auto biggest = *it;

	for (it; it != my_container.end(); ++it) {
		if (*it > biggest)
			biggest = *it;
	}

	return biggest;
}*/

int main() {

	std::vector<int> my_vec = { 1, 2, 3 };
	std::list<int> my_list = { 1, 2, 4 };

	std::cout << find_max<std::vector, int>(my_vec) << std::endl;
	std::cout << find_max<std::list, int>(my_list) << std::endl;

	return 0;
}
