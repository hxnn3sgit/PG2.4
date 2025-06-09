#include <iostream>
#include <string>

using std::cout, std::endl, std::string;

class custom_exception : public std::exception {
	virtual const char *what() const noexcept {
		return "custom exception text out of custom exception class";
	}
};

int main() {
	
	try {
		//int *array = new int[929399999999];
		throw custom_exception();
	} catch (std::bad_alloc &e) {
		cout << "thrown exception: " << e.what() << endl;
	} catch(custom_exception &e) {
		cout << "custom exception out of custom catch block: " << e.what() << endl;
	}
	catch (std::exception &e) {
		cout << "custom exception: " << e.what() << endl;
	}

	cout << "after exception" << endl;
	


	return 0;
}
