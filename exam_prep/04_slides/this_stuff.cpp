#include <iostream>

class Builder {
private:
	int X;
	int Y;
public:
	Builder() = default;
	~Builder() = default;
	Builder& setX(int x);
	Builder& setY(int y);
};

struct Person {
	std::string name;
	int age;
	Person(const std::string &name, const int age) : name(name), age(age) {}
	~Person() = default;
	Person(const Person &other) = delete;
	Person(Person &&other) = delete;
	Person& operator=(const Person &other) = delete;
	Person& operator=(Person &&other) = delete;
	//std::ostream& operator<<(std::ostream& out, const Person &my_person);
};

std::ostream& operator<<(std::ostream& out, const Person &my_person) {
	out << my_person.name << ", " << my_person.age;
	return out;
}

Builder& Builder::setX(int x) {
	X = x;
	return *this;
}

Builder& Builder::setY(int y) {
	Y = y;
	return *this;
}

int main() {
	Builder b;
	b.setX(10).setY(10);

	Person me("Hannes", 23);
	std::cout << me << std::endl;

	return 0;
}
