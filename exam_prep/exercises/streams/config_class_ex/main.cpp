#include "config.h"
#include <fstream>
#include <cassert>

int main() {
    // --- Teil 1: Config erstellen und in Datei schreiben ---
    Config cfg_out;
    cfg_out.set("user", "hannes");
    cfg_out.set("version", "1.2.3");
    cfg_out.set("fullscreen", "false");

    std::cout << "--> Schreibe Konfiguration in config.txt..." << std::endl;
    {
        std::ofstream outfile("config");
        outfile << "# Generierte Konfigurationsdatei\n\n";
        outfile << "  # Ein paar Einstellungen\n";
        outfile << cfg_out;
    }
    std::cout << "--> Fertig.\n" << std::endl;


    // --- Teil 2: Config aus Datei lesen und verifizieren ---
    Config cfg_in;
    std::cout << "--> Lese Konfiguration aus config.txt..." << std::endl;
    {
        std::ifstream infile("config.txt");
        infile >> cfg_in;
    }
    std::cout << "--> Fertig.\n" << std::endl;


    // --- Teil 3: Ausgabe und Überprüfung ---
    std::cout << "--> Gelesene Konfiguration:" << std::endl;
    std::cout << cfg_in;

    // Überprüfe die Werte
    assert(cfg_in.has("user"));
    assert(*cfg_in.get("user") == "hannes");
    assert(*cfg_in.get("version") == "1.2.3");
    assert(!cfg_in.has("nicht_da"));
    
    std::cout << "\n--> Alle Tests erfolgreich!" << std::endl;

    return 0;
}
