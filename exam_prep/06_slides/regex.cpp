#include <iostream>
#include <regex>
#include <string>
#include <iterator>

// filter valid emails out of a string exercise


int main() {
        std::string text = R"(User1: max.mustermann@example.com
        Fehlerhafte Adresse: test@.com
        User2: anna_meier@st.oth-regensburg.de
        No-Mail: hallo-welt@
        )";

	std::regex pattern(R"([a-zA-Z0-9][a-zA-Z0-9_.-]*@[a-zA-Z][a-zA-Z0-9_.-]{1,62}[a-zA-Z]\.[a-zA-Z]{1,3})");

	auto words_begin = std::sregex_iterator(text.begin(), text.end(), pattern);
	auto words_end = std::sregex_iterator();

	std::cout << "Found " << std::distance(words_begin, words_end) << " matches." << std::endl;

	for (std::regex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		std::cout << match_str << "\n";
	}	

	return 0;
}
