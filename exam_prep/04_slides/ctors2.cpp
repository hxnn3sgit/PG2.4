#include <iostream>
#include <string>

using std::cout, std::endl, std::string;

class RessourceBox {
private:
	int *value;
public:
	RessourceBox(); // default ctor
	~RessourceBox() { delete value; }
	explicit RessourceBox(int value); // no automatic cast
	RessourceBox(const RessourceBox &other);
	RessourceBox(RessourceBox &&other) noexcept; // move
	RessourceBox& operator=(RessourceBox &&other); // move assign op
	RessourceBox& operator=(const RessourceBox &other); // copy assign op
};

RessourceBox::RessourceBox() {
	value = new int(0);
}

RessourceBox::RessourceBox(int value) {
	this->value = new int(value);
}

RessourceBox::RessourceBox(const RessourceBox &other) {
	value = new int(*other.value);
}

RessourceBox::RessourceBox(RessourceBox &&other) noexcept {
	value = other.value;
	other.value = nullptr;
}

RessourceBox& RessourceBox::operator=(RessourceBox &&other) {
	delete value;
	value = other.value;
	other.value = nullptr;
	
	return *this;
}

RessourceBox& RessourceBox::operator=(const RessourceBox &other) {
	if (this == &other)
		return *this;

	delete value;
	value = new int(*other.value);
	
	return *this;
}

class NamedRessourceBox : public RessourceBox {
private:
	string name;
	const int id;
public:
	NamedRessourceBox() = default;
	NamedRessourceBox(const string &name, const int value, const int id) : RessourceBox(value), name(name), id(id) {}
	
};

int main() {
	RessourceBox a(5);
	RessourceBox b = a;
	RessourceBox c = std::move(a);
	NamedRessourceBox nrb("Box1", 42, 1);
	// NamedRessourceBox n2 = nrb
}
