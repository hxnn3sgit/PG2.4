#include <iostream>

enum class ProcessState : unsigned char {
	Created,
	Running,
	Suspended,
	Terminated
};

enum AccessRights {
	Read = 0x1,
	Write = 0x2,
	Execute = 0x4
};

AccessRights operator|(AccessRights lhs, AccessRights rhs) {
	int underlying_lhs = static_cast<int>(lhs);
	int underlying_rhs = static_cast<int>(rhs);
	
	int result_as_int = underlying_lhs | underlying_rhs;

	return static_cast<AccessRights>(result_as_int);
}

AccessRights operator&(AccessRights lhs, AccessRights rhs) {
	int underlying_lhs = static_cast<int>(lhs);
	int underlying_rhs = static_cast<int>(rhs);
	
	int result_as_int = underlying_lhs & underlying_rhs;

	return static_cast<AccessRights>(result_as_int);
}

void print_rights(AccessRights rights) {
	std::cout << "Access rights: ";
	if (rights & Read)
		std::cout << "Read ";
	if (rights & Write)
		std::cout << "Write ";
    if (rights & Execute)
   		std::cout << "Execute ";

	std::cout << std::endl;	
}

const char* to_string(ProcessState state) {
	switch(state) {
	case ProcessState::Created: return "Created";
	case ProcessState::Running: return "Running";
	case ProcessState::Suspended: return "Suspended";
	case ProcessState::Terminated: return "Terminated";
	default: return "Unknown";
	}
}

std::ostream& operator<<(std::ostream &out, AccessRights rights) {
	out << __PRETTY_FUNCTION__ << std::endl;
	out << "Access rights: ";
	if (rights & Read)
		out << "Read ";
	if (rights & Write)
		out << "Write ";
    if (rights & Execute)
   		out << "Execute ";

	return out;	
}

bool is_active(ProcessState state) {
	switch(state) {
		case ProcessState::Running: return true;
		case ProcessState::Suspended: return true;
		case ProcessState::Created: return false;
		case ProcessState::Terminated: return false;
	}
	return false;
}

int main() {
	unsigned char terminated = static_cast<unsigned char>(ProcessState::Terminated);
	std::cout << static_cast<int>(terminated) << std::endl;
	std::cout << to_string(ProcessState::Terminated) << std::endl;
	std::cout << is_active(ProcessState::Running) << std::endl;

	AccessRights rights = Read | Write;
	std::cout << rights << std::endl;

	return 0;
}
