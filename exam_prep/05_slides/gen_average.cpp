#include <iostream>
#include <exception>
#include <concepts>

class divide_by_zero : public stdj::runtime_error {
	public:
		virtual const char *what() const noexcept {
			return "Division by zero";
		}
};

template<typename T>
concept Averageable = requires (const T &a, const T &b) {
	a + b;
	T result = (a + b) / 2;
	typename T::double;
}

template<typename T>
T average(const T &a, const T &b) requires Averagable<T, T> {
	return (a + b) / 2.0;
}


int main() {

	return 0;
}
