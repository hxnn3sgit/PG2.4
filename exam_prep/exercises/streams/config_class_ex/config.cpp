#include <iostream>
#include <string>
#include <sstream>

#include "config.h"

bool Config::has(const std::string &key) const {
	// assumption, first entry in std::map is key, second is value

	if (data_.find(key) != data_.end())
		return true;
	return false;
}

std::optional<std::string> Config::get(const std::string &key) const {
	std::map<std::string, std::string>::const_iterator pos = data_.find(key);
	if (pos == data_.end())
		return std::nullopt;
	else {
		std::string map_value = pos->second;
		return map_value;
	}

}

void Config::set(const std::string &key, const std::string &value) {
	std::pair<std::string, std::string> pair_to_insert(key, value);
	data_.insert_or_assign(pair_to_insert);
}

std::ostream& operator<<(std::ostream &os, const Config &cfg) {
	for (const auto &kv_pair : cfg.data_)
		os << kv_pair.first << " = " << kv_pair.second << std::endl;

	return os;
}

bool is_comment(const std::string line) {
	std::istringstream iss(line);
	std::string first_token;
	iss >> first_token;
	
	if (first_token == "#")
		return true;
	else
		return false;
}

std::istream& operator>>(std::istream &is, Config &cfg) {
	// delete remaining config:
	cfg.data_.clear();

	// iterate line by line through istream:
	
	std::string line;
	while (std::getline(is, line)) { // goes until newline character
		if (!is_comment(line)) {
			// process every line in there
			std::istringstream iss(line);
		
			std::string word;
			while (iss >> word) {
				std::cout << "[LOGGER INFO:] word is going to be processed: " << word << std::endl;
				word += " ";
				is >> word;
			}
		}
	}



	return is;
}
