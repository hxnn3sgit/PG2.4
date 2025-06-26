#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Benutzer;
class Film;
class Buch;

class Medium {
protected:
	std::string Titel;
	int DauerInMinuten;
public:
	Medium() = default;
	explicit Medium(const std::string &titel, const int DauerInMinuten) : Titel(titel), DauerInMinuten(DauerInMinuten) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual ~Medium() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	virtual void anzeigen() {
		std::cout << "Titel: " << Titel << ", Dauer in Minuten: " << DauerInMinuten << std::endl;
	}
};

class Buch : public Medium {
	std::string Autor;
public:
	Buch() = default;
	Buch(const std::string &titel, const int DauerInMinuten, const std::string &autor)	
		: Medium(titel, DauerInMinuten), Autor(autor) {}
	~Buch() {}
	void anzeigen() override {
		std::cout << "titel/Dauer in Min/Autor: " << Titel << ", " << DauerInMinuten << ", " << Autor << std::endl;
	}
};

class Film : public Medium {
public:
	std::string Regisseur;
	std::vector<std::weak_ptr<Benutzer>> hauptdarsteller;
public:
	Film() = default;
	Film(const std::string &titel, const int dauerInMinuten, const std::string &regisseur)
		: Medium(titel, dauerInMinuten), Regisseur(regisseur) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	~Film() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	void anzeigen() override {
		std::cout << "titel/Dauer in Minuten/Autor: " << Titel << ", " <<DauerInMinuten << ", " << Regisseur << std::endl;
	}
};

class Benutzer {
	std::string Name;
	std::shared_ptr<Medium> LieblingsMedium;
public:
	Benutzer() = default;
	Benutzer(const std::string &name) : Name(name) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	~Benutzer() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
	
	void setzeLieblingsmedium(std::shared_ptr<Medium> medium) {
		LieblingsMedium = medium;
	}

	void zeigeLieblingsmedium() {
		if (LieblingsMedium)
			std::cout << "Lieblingsmedium: " << LieblingsMedium << std::endl;
		else
			std::cout << "Kein Lieblingsmedium gesetzt!\n";
	}
};
void problem_zyklus() {
	std::shared_ptr<Film> mein_film = std::make_shared<Film>("F&F5",  120, "Gary Thompson");
	std::shared_ptr<Benutzer> b1 = std::make_shared<Benutzer>("b1");
	
	b1->setzeLieblingsmedium(mein_film);

	mein_film->hauptdarsteller.push_back(b1);
}
/*void nutzung_shared_pointers() {
	std::shared_ptr<Buch> mein_buch = std::make_shared<Buch>("Harry Potter", 360, "J. K. Rowling");
	std::shared_ptr<Film> mein_film = std::make_shared<Film>("F&F 5", 120, "Gary Scott Thompson");
}*/

void verwaltung_raw_pointers() {
	Buch *mein_buch = new Buch("Harry Potter", 360, "J. K. Rowling");
	Film *mein_film = new Film("F&f 5", 120, "Gary Scott Thompson");

	std::vector<Medium*> meine_medien = { mein_buch, mein_film };

	for(const auto &medium : meine_medien) {
		medium->anzeigen();
	}

	delete mein_buch;
	delete mein_film;
	
	meine_medien.clear();

	// oder zuerst clear? -> keine dangling pointer
}

void verwaltung_smart_pointers() {
	std::unique_ptr<Buch> mein_buch = std::make_unique<Buch>("Harry Potter", 360, "J. K. Rowling");
	std::unique_ptr<Film> mein_film = std::make_unique<Film>("F&F 5", 120, "Gary Scott Thompson");

	std::vector<std::unique_ptr<Medium>> meine_medien;

	meine_medien.push_back(std::move(mein_buch));
	meine_medien.push_back(std::move(mein_film));

	for (const auto &medium : meine_medien) {
		 medium->anzeigen();
	}
	
}

void nutzung_shared_pointers() {
	std::shared_ptr<Film> mein_film = std::make_shared<Film>("F&F5", 120, "Garry scott");

	Benutzer b1("b1");
	Benutzer b2("b2");
	Benutzer b3("b3");
	
	b1.setzeLieblingsmedium(mein_film);
	b2.setzeLieblingsmedium(mein_film);

	b1.zeigeLieblingsmedium();
	b2.zeigeLieblingsmedium();
	b3.zeigeLieblingsmedium();

	b1.setzeLieblingsmedium(nullptr);

}

int main() {
	std::cout << "raw pointer verwaltung:\n";
	verwaltung_raw_pointers();
	std::cout << "\n\nsmart pointer verwaltung:\n";
	verwaltung_smart_pointers();
	std::cout << "\n\nshared pointers:\n";
	nutzung_shared_pointers();

	std::cout << "\n\nzyklus problem:\n";
	problem_zyklus();

	return 0;
}
