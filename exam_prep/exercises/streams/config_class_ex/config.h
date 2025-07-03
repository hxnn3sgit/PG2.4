#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>
#include <map>
#include <optional>

class Config {
private:
    std::map<std::string, std::string> data_;

public:
    // Prüft, ob ein Schlüssel existiert
    bool has(const std::string& key) const;

    // Holt einen Wert. Gibt std::nullopt zurück, wenn der Schlüssel nicht existiert.
    std::optional<std::string> get(const std::string& key) const;

    // Setzt oder überschreibt einen Wert.
    void set(const std::string& key, const std::string& value);

    // Deklaration der Stream-Operatoren als Freunde, damit sie
    // auf die privaten Member (data_) zugreifen können.
    friend std::ostream& operator<<(std::ostream& os, const Config& cfg);
    friend std::istream& operator>>(std::istream& is, Config& cfg);
};

// Deklaration der freien Funktionen
std::ostream& operator<<(std::ostream& os, const Config& cfg);
std::istream& operator>>(std::istream& is, Config& cfg);

#endif // CONFIG_H
