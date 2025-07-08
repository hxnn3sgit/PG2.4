#include <iostream>
#include <map>
#include <unordered_map>
#include <string>

struct cityRecord {
    std::string name;
    std::string country;
    int population;
    double area;

	cityRecord() = default;	
	cityRecord(const std::string &n, const std::string &c, int p, double a)
	   : name(n), country(c), population(p), area(a) {}	
};

int main() {
	std::map<std::string, cityRecord> cityMap;

	cityRecord berlinData;
	berlinData.name = "Berlin";
	berlinData.country = "Germany";
	berlinData.population = 3000000;
	berlinData.area = 372.21;
	cityMap["Berlin"] = std::move(berlinData); // wenn ctor existieren würde, könnte man direkt intialisieren
	
	cityMap.insert(std::make_pair("Melbourne", cityRecord({"Melbourne", "Australia", 239029, 203.23})));
	cityMap.emplace("London", cityRecord{"London", "GB", 232132, 103.23});


	for (auto &[key, value] : cityMap)
		std::cout << key << ", " << value.population << std::endl;

	// vermeidung von auto keyword
	std::map<std::string, cityRecord>::iterator search = cityMap.find("Berlin");
	if (search != cityMap.end())
		std::cout << search->second.population << ", " << search->second.country << std::endl;
	else
		std::cout << "Berlin not found\n";
	std::cout << std::endl;

	cityMap.erase("London");

	for (auto &[key, value] : cityMap)
		std::cout << key << ", " << value.country << std::endl;
	std::cout << std::endl;

	try {	
	cityMap.erase("London");
	} catch (std::exception &e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}

	cityRecord& londonData = cityMap["London"];
	londonData.population = 230913;
	londonData.area = 23.23;
	londonData.country = "GB";

	for (auto &[key, value] : cityMap)
		std::cout << key << ", " << value.country << std::endl;

	const std::map<std::string, cityRecord>& constMap(cityMap);

	std::cout << "\nconst map\n";
	for (auto &[key, value] : constMap)
		std::cout << key << ", " << value.country << std::endl;

	return 0;
}
