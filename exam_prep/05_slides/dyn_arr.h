#include <iostream>
#include <string>

// Iterator class:

template<typename dyn_arr>
class dyn_arr_Iterator {

public:
	using ValueType = typename dyn_arr::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	dyn_arr_Iterator(PointerType ptr) : m_Ptr(ptr) {}
	dyn_arr_Iterator& operator++() {
		m_Ptr++;
		return *this;
	}
	dyn_arr_Iterator operator++(int) {
		dyn_arr_Iterator iterator = *this;
		++(*this);
		return iterator;
	}

	dyn_arr_Iterator& operator--() {
		m_Ptr--;
		return *this;
	}
	dyn_arr_Iterator operator--(int) {
		dyn_arr_Iterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index) {
		return *(m_Ptr + index);
	}

	PointerType operator->() {
		return m_Ptr;
	}

	PointerType operator*() {
		return *m_Ptr;
	}

	bool operator==(const dyn_arr_Iterator &other) const {
		return m_Ptr == other.m_Ptr;
	}

	bool operator!=(const dyn_arr_Iterator &other) const {
		return !(*this == other);
	}
 private:
	PointerType m_Ptr;
};

template<typename T>
class dyn_arr {
	T *data;
	int capacity; // maximum capacity of array
	int size; // how many current elements
public:
	dyn_arr() : data(nullptr), size(0), capacity(0) {}
	dyn_arr(int capacity) : data(new T[capacity]), capacity(capacity), size(0) {}
	dyn_arr(const dyn_arr &other);
	dyn_arr(dyn_arr &&other);
	dyn_arr operator=(const dyn_arr &other);
	dyn_arr& operator=(dyn_arr &&other);
	~dyn_arr() { delete [] data; }

	void resize();
	void push_data_back(const T &value);
	void pop_data_back();	
	T& at(const int index);
	const T at(const int index) const;
	T operator[](const int index) const { return data[index]; }
	const T& operator[](const int index) { return data[index]; }
	int arr_size() { return size; }
	int current_capacity() { return capacity; }
	bool empty() { return !size; } // if size == 0 -> return true, else false
	bool full() { return size == capacity; }
	void clear();

	class Iterator {
		T *cur_elem_ptr;
	public:
		Iterator(T* start) : cur_elem_ptr(start) {}
		T& operator*() { return *cur_elem_ptr; };
		T* operator->() { return cur_elem_ptr; };
		
		Iterator& operator++() { // prefix
			cur_elem_ptr++;
			return *this;
		}
		Iterator operator++(int) { // postfix
			Iterator before_increment = *this;
			++(*this);
			return before_increment;
		}
		Iterator& operator--() { // prefix
			cur_elem_ptr--;
			return *this;
		}

		Iterator operator--(int) { // postfix
			Iterator before_increment = *this;
			--(*this);
			return before_increment;
		}

		bool operator==(const Iterator &other) const {
			return cur_elem_ptr == other.cur_elem_ptr;
		}
		bool operator!=(const Iterator &other) const {
			return cur_elem_ptr != other.cur_elem_ptr;
		}
	};
	
	Iterator begin();
	Iterator end();

	template<typename U>
	friend std::ostream& operator<<(std::ostream& out, const dyn_arr<U> &my_arr);
};

template<typename T>
void dyn_arr<T>::resize() {
	if (capacity == 0)
		capacity = 1;
	else
		capacity *= 2;
	
	T *new_data = new T[capacity];
	for (int i = 0; i < size; ++i)
		new_data[i] = data[i];

	delete [] data;
	data = new_data;
 }

template<typename T>
void dyn_arr<T>::clear() {
	delete [] data;
	data = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
dyn_arr<T>::dyn_arr(dyn_arr<T> &&other) {
	// move data
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	
	// clean up old memory
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

template<typename T>
dyn_arr<T>& dyn_arr<T>::operator=(dyn_arr<T> &&other) {
	if (this != other) {
		delete [] data; 
		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}

	return *this;
}

template<typename T>
dyn_arr<T>::dyn_arr(const dyn_arr<T> &other) {
	// make deep copy; allocate same memory; copy data bytewise
	if (other.empty()) {
		std::cerr << "empty array can't be copied" << std::endl;
	} else {
		data = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;
		for (int i = 0; i < size; ++i)
			data[i] = other.data[i];
	}
}

template<typename T>
dyn_arr<T> dyn_arr<T>::operator=(const dyn_arr<T> &other) {
	if (*this != other) {
		delete [] data;
		data = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;

		for (int i = 0; i < size; ++i)
			data[i] = other.data[i];
	}
	
	return *this;
}

template<typename T>
T& dyn_arr<T>::at(const int index) {
	if (index >= 0 && index < size) {
		// not out of bounds, okay
		return data[index];
	} else {
		std::cerr << "index out of bounds!" << std::endl;
		throw std::out_of_range("Index out of range");
	}
}

template<typename T>
const T dyn_arr<T>::at(const int index) const {
	if (index >= 0 && index < size) {
		// not out of bounds, okay
		return data[index];
	} else {
		throw std::out_of_range("Index out of range");
	}
}

template<typename T>
void dyn_arr<T>::pop_data_back() {
	if (empty()) {
		std::cerr << "vector is empty, nothing to pop back!" << std::endl;
	} else {
		--size;
		// eventually, implement method to shrink the array
	}
}

template<typename T>
void dyn_arr<T>::push_data_back(const T &value) {
	if (full())
		resize();
	data[size++] = value;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const dyn_arr<T> &my_arr) {
	for (int i = 0; i < my_arr.size; ++i)
		out << "[" << my_arr.data[i] << "]\t";
	
	return out;
}