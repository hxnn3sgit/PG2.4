#include <iostream>

class Counter {
private:
    int id;
    // TODO: Deklariere eine Membervariable, die zählt, wie viele Objekte aktuell existieren
	static int object_counter;
public:
    Counter() : id(++object_counter) {}     // Konstruktor
    ~Counter() { --object_counter; }    // Destruktor

    int getId() const {
    // TODO: Deklariere eine Memberfunktion, die die Anzahl der existierenden Objekte zurückgibt
		return id;
	}

	static int get_number_of_objects() {
		return object_counter;
	}
};

int Counter::object_counter = 0;

int main() {
	Counter my_counter;
	Counter second_counter;

	return 0;
}
