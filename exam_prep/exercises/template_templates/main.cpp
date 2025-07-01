#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Ihre Implementierung von ContainerAdapter kommt hier hin

template<
	template <typename, typename> class Container,
	typename T
>
class ContainerAdapter {
	Container<T, std::allocator<T>> data;
public:
	ContainerAdapter() = default;
	void add(const T& value) { data.push_back(value); }
	T get_last_and_remove() {
		if (data.empty())
			throw std::runtime_error("Container is empty!");
		T last_element = data.back();
		data.pop_back();
		return last_element;
	}
	void print() const {
		for (const auto &element : data)
			std::cout << element << " ";
		std::cout << std::endl;
	}
};

int main() {
    // Adapter mit std::vector und int
    ContainerAdapter<std::vector, int> vec_adapter;
    vec_adapter.add(10);
    vec_adapter.add(20);
	vec_adapter.add(30); 
    
    std::cout << "Vector Adapter Inhalt: ";
    vec_adapter.print();
	
	try {
    int last_val = vec_adapter.get_last_and_remove();
    std::cout << "Entferntes Element: " << last_val << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << "exception occured: " << e.what() << std::endl;
	}
    
    std::cout << "Vector Adapter nach get_last(): ";
    vec_adapter.print();

    std::cout << "--------------------------" << std::endl;

    // Adapter mit std::list und double
    ContainerAdapter<std::list, double> list_adapter;
    list_adapter.add(3.14);
    list_adapter.add(2.71);

    std::cout << "List Adapter Inhalt: ";
    list_adapter.print();

    return 0;
}
