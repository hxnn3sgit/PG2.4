#include <iostream>

class Counter {
private:
	int id;
    static int id_counter;
    // TODO: Deklariere eine Membervariable, die zählt, wie viele Objekte aktuell existieren
	static int object_counter;
public:
    Counter() : id(++id_counter) { ++object_counter; }     // Konstruktor
    ~Counter() { --object_counter; }    // Destruktor

    int getId() const {
    // TODO: Deklariere eine Memberfunktion, die die Anzahl der existierenden Objekte zurückgibt
		return id);
	}

	static int get_number_of_objects() {
		return object_counter;
	}
};

int Counter::id_counter = 0;
int Counter::object_counter = 0;

int main() {
    Counter a;
    Counter b;
    {
        Counter c;
        std::cout << "Objekte aktuell: " << Counter::get_number_of_objects() << "\n";
        std::cout << "ID von c: " << c.getId() << "\n";
    } // c wird hier automatisch zerstört
    std::cout << "Objekte aktuell: " << Counter::get_number_of_objects() << "\n";

    Counter d;
    std::cout << "ID von d: " << d.getId() << "\n";

    return 0;
}
