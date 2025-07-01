



#include <iostream>
#include <string>
#include <vector>

#include "../../my_own_librarys/dyn_arr/dyn_arr.h"
#include "../../my_own_librarys/linked_list/linked_list.h"

class Tier {
protected:
	std::string Name;
	unsigned int AnzahlBeine;
public:
	// Methode: muss mit virtual deklariert werden, um ggf. überschrieben werden zu können
	// Tier() = delete;
	explicit Tier(const std::string &name, unsigned int anzahl_beine)
				: Name(name), AnzahlBeine(anzahl_beine) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void print_name();
	virtual void print_number_of_legs();

	friend std::ostream& operator<<(std::ostream &out, const Tier &other);
};

std::ostream& operator<<(std::ostream &out, const Tier &other) {
	
	return out << "\noperator<<";
}

class Säugetier : public Tier {
// same membervars as Tier
public:
	// Säugetier() = delete;
	Säugetier(const std::string &name, unsigned int anzahl_beine)
			: Tier(name, anzahl_beine) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void print_name() override;
	virtual void print_number_of_legs() override;
};

class Insekt : public Tier {
public:	
	Insekt() = delete;
	Insekt(const std::string &name, unsigned int anzahl_beine)
		: Tier(name, anzahl_beine) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void print_name() override;
	virtual void print_number_of_legs() override;
};

class Zootier {
	public:
		virtual void fuettern() const = 0;
	};

class Pferd : public Säugetier, public Zootier {
public:
	Pferd() = delete;
	Pferd(const std::string &name, unsigned int anzahl_beine)
		: Säugetier(name, anzahl_beine) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void print_name() override;
	virtual void print_number_of_legs() override;
	virtual void fuettern() const override { std::cout << "Pferd wird gefüttert\n"; }
};

class Biene : public Insekt, public Zootier {
public:
	Biene() = delete;
	Biene(const std::string &name, unsigned int anzahl_beine)
		: Insekt(name, anzahl_beine) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void print_name() override final;
	virtual void print_number_of_legs() override final;
	virtual void fuettern() const override { std::cout << "Biene wird gefüttert\n"; }
};

class Katze : public Säugetier, public Zootier {
public:
	Katze() = delete;
	explicit Katze(const std::string &name, unsigned int anzahl_beine)
			: Säugetier(name, anzahl_beine) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void print_name() override final;
	virtual void print_number_of_legs() override final;
	virtual void fuettern() const override { std::cout << "Katze wird gefüttert\n"; }
	
	
};

class Zoo {
public:
	LinkedList<Zootier*> tiere;
};

class Tierpfleger {
private:
	std::string Name;
public:
	Tierpfleger(const std::string &name) : Name(name) {}
	void fuettern(Zootier &other) const {
		other.fuettern();
	}
};


int main() {
	Pferd mein_pferd("Amadeus", 4);
	Biene meine_biene("Maya", 6);
	Katze meine_katze("Layla", 4);

	LinkedList<Tier*> meine_tiere;

	meine_tiere.append(&mein_pferd);
	meine_tiere.append(&meine_biene);
	meine_tiere.append(&meine_katze);

	for (const auto &element : meine_tiere) {
		element->print_name();
		element->print_number_of_legs();
	}

	Tierpfleger me("Hannes");

	Zoo mein_zoo;

	mein_zoo.tiere.append(&mein_pferd);
	mein_zoo.tiere.append(&meine_biene);
	mein_zoo.tiere.append(&meine_katze);

	for (auto &zootier : mein_zoo.tiere)
		me.fuettern(*zootier);


	std::cout << mein_pferd << std::endl;
	std::cout << meine_katze << std::endl;

	return 0;
}

void Tier::print_name() { std::cout << "Tier heißt " << Name << std::endl; }

void Tier::print_number_of_legs() { std::cout << "Tier hat " << AnzahlBeine << " Beine\n"; }

void Säugetier::print_name() { std::cout << "Säugetier heißt " << Name << std::endl; }

void Säugetier::print_number_of_legs() { std::cout << "Säugetier hat " << AnzahlBeine << " Beine\n"; }

void Insekt::print_name() { std::cout << "Insekt heißt " << Name << std::endl; }

void Insekt::print_number_of_legs() { std::cout << "Insekt hat " << AnzahlBeine << " Beine\n"; }

void Pferd::print_name() { std::cout << "Pferd heißt " << Name << std::endl; }

void Pferd::print_number_of_legs() { std::cout << "Pferd hat " << AnzahlBeine << " Beine\n"; }

void Biene::print_name() { std::cout << "Biene heißt " << Name << std::endl; }

void Biene::print_number_of_legs() { std::cout << "Biene hat " << AnzahlBeine << " Beine\n"; }

void Katze::print_name() { std::cout << "Katze heißt " << Name << std::endl; }

void Katze::print_number_of_legs() { std::cout << "Katze hat " << AnzahlBeine << " Beine\n"; }