#include <iostream>
#include <vector>
#include <string>
#include <functional>

int main() {
    std::vector<std::string> wörter = { "Apfel", "Banane", "Computer", "Katze", "Haus", "Baum" };

    auto startsWithB = [](const std::string &word) {
		return !word.empty() && word[0] == 'B';
	};
	
	auto lengthBiggerFive = [](const std::string &word) {
		return word.length() > 5;
	};	


    auto filterUndAusgeben = [](const std::vector<std::string> &liste, std::function<bool(const std::string&)> kriterium) -> void {
        for (const auto &element : liste) {
        	if (kriterium(element))
				std::cout << element << std::endl;
		}
    };

	std::cout << "startsWithB:\n";
    filterUndAusgeben(wörter, startsWithB);
	std::cout << "lengthBiggerFive:\n";
	filterUndAusgeben(wörter, lengthBiggerFive);
	// filterUndAusgeben(wörter, 

    return 0;
}
