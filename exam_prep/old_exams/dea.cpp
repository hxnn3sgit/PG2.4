#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <exception>
#include <filesystem>
#include <fstream>
#include <cassert>

namespace fs = std::filesystem;

struct state {
	std::string name;
	std::map<char, state*> transitions;
	bool accepting = false;
};

class dea {
private:
	std::string alpha;
	state* states;
	int n_states;
	state* start;
public:
	dea() {}
	dea(const dea &other);
	dea(dea &&other) noexcept;
	~dea() noexcept ;

	void load_from_file(const fs::path &p);
	state* find(const std::string &name);
	bool check_states();
	bool operator()(const std::string &wort);
	// bool operator()(const std::string &wort, std::functional<)
private:
    void load_alphabet(const std::string &line);
    void load_states(const std::string &line);
    void assign_start_state(const std::string &line);
    void tag_accepting_states(const std::string &line);
    void single_transitions(const std::string &line);
};

dea::dea() : alpha(""), states(nullptr), n_states(0), start(nullptr) {}
dea::dea(const dea &other) {
	alpha = other.alpha;
	states = new state[other.n_states];
	for (int i = 0; i < other.n_states; ++i) {
		states[i] = other.states[i];
	}
	n_states = other.n_states;
	start = other.start;
}

dea::dea(dea &&other) noexcept {
	alpha = other.alpha;
	states = other.states;
	n_states = other.n_states;
	start = other.start;

	other.alpha = "";
	other.states = nullptr;
	other.n_states = 0;
	other.start = nullptr;
}

dea::~dea() noexcept {
	delete [] states;	
}

class invalid_description : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "invalid description of DEA in file";
    }
};

class invalid_input : public std::exception {
    char c;
public:
    invalid_input(char c) : c(c) {}
    
    virtual const char* what() const noexcept override {
        return "invalid input character";
    }
};

int main(int argc, char **argv) {
	if (argc == 3) {
		fs::path p = argv[1];
		std::string word_to_check = argv[2];
		
		dea my_dea;
		if (fs::exists(p)) {
			try {
				my_dea.load_from_file(p);
			} catch (invalid_description &e) {
				std::cerr << "Exception während Einlesen des DEAs: " << e.what() << std::endl;
				return EXIT_FAILURE;
			}

			try {
				bool successful_operation = my_dea(word_to_check);
				if (successful_operation)
					std::cout << "Wort " << word_to_check << " ist vom DEA akzeptiert worden\n";
				else
					std::cout << "Wort " << word_to_check << " ist nicht vom DEA akzeptiert worden\n";
			} catch (invalid_input &e) {
				std::cerr << "excpetion during reading word: " << e.what() << std::endl;
				return EXIT_FAILURE;
			}
		} else {
			std::cerr << "Datei nicht vorhanden\n";
			return EXIT_FAILURE;
		}

	} else {
		std::cerr << "Nicht genügend oder zu Viele Argumente: Benötigt: 1: DEA-Datei, 2: Zu prüfendes Wort\n";
		return EXIT_FAILURE;
	 }

	return EXIT_SUCCESS;
}

state* dea::find(const std::string &name) {
	// ich würde mal sagen, diese Funktion geht duch mein dea::states array, checkt ob states.name == name,
	// falls ja return den state, falls nicht return nullptr
	
	for (int i = 0; i < n_states; ++i) {
		if (states[i].name == name) {
			return &states[i];
		}
	}

	return nullptr;
}

void dea::load_alphabet(const std::string &line) {
	std::istringstream alphabet_iss(line);
	std::string alphabet;
	while (std::getline(alphabet_iss, alphabet, ' '))
		alpha += alphabet; // cat single chars
}

void dea::load_states(const std::string &line) {
	std::istringstream states_iss(line);
 	std::string single_state;
	n_states = 0;
	std::vector<std::string> string_states; 
	while (std::getline(states_iss, single_state,' ')) {
		n_states += 1;
		string_states.push_back(single_state);
	}

	states = new state[n_states];

	for (int i = 0; i < n_states; ++i) {
		states[i].name = string_states[i];
	}
}

void dea::assign_start_state(const std::string &line) {
	state* start_state = find(line);
	if(start_state) {
		start = start_state;
	} else {
		std::cerr << "start state not found\n";
		throw invalid_description();
	}
}

void dea::tag_accepting_states(const std::string &line) {
	std::istringstream accepting_states_stream(line);
	std::string accepting_state_name;
	std::vector<std::string> accepting_state_names;
	while (std::getline(accepting_states_stream, accepting_state_name, ' '))
		accepting_state_names.push_back(accepting_state_name);

	for (const auto &name : accepting_state_names) {
		state *set_to_accept = find(name);
		if (set_to_accept != nullptr)
			set_to_accept->accepting = true;
		else {
			throw invalid_description();
		}
	}
}

void dea::single_transitions(const std::string &line) {
	std::istringstream transition_stream(line);
	std::string transition_state;

	char letter;
	std::string origin_state;
	std::string other_state;

	std::getline(transition_stream, transition_state, ' ');
	origin_state = transition_state;

	std::getline(transition_stream, transition_state, ' ');
	assert(transition_state.length() == 1);
	letter = transition_state[0];

	std::getline(transition_stream, transition_state, ' ');
	other_state = transition_state;

	state* state_to_add_transition = find(origin_state);
	state_to_add_transition->transitions.insert(std::pair{letter, find(other_state)});
}

void dea::load_from_file(const fs::path &p) {
	using iss = std::istringstream;
	std::ifstream fin(p);
	std::string line;
	
	#define read_line_and_check_error \
        if (!std::getline(fin, line)) throw invalid_description()

	
	read_line_and_check_error; 
	load_alphabet(line);
	read_line_and_check_error; 
	load_states(line);
	read_line_and_check_error; 
	assign_start_state(line);
	read_line_and_check_error; 
	tag_accepting_states(line);

	while(std::getline(fin, line))
		single_transitions(line);

	if (!check_states())
		throw invalid_description();
}

bool dea::check_states() {
	// for every state, for every letter in alphabet there must be a transition
	
	for (int i = 0; i < n_states; ++i) {
		for (int j = 0; j < alpha.length(); ++j) {
			if (states[i].transitions.find(alpha[j]) == states[i].transitions.end())
				return false;
		}
	}

	return true;
}

bool dea::operator()(const std::string &wort) {
	// iterate somehow through the transitions map,
	// if accepting after fnishing the word is true,
	// return true, else false
	
	state* current_state = start;
	std::string next_state_name;
	for (int i = 0; i < wort.length(); ++i) { // if works everytime, because everything was validated before
		if (auto search = current_state->transitions.find(wort[i]); search != current_state->transitions.end())
			next_state_name = search->second->name;
		current_state = find(next_state_name);
	}

	return current_state->accepting;
}
