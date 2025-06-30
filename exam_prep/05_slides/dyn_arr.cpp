#include "dyn_arr.h"
/*
template<typename T>
void DynArr<T>::push_data_back(const T &value) {
	if (!full()) {
		data[size] = value; // value is assigned to right place 
		++size;
	} else {
		// implement logic for extending size
		if (capacity == 0) {
			capacity = 1;
		}	
		capacity *= 2; // double capacity everytime new storage is needed
		T *new_data = new T[capacity];
		for (int i = 0; i < size; ++i)
			new_data[i] = data[i];

		new_data[size] = value; // assign value
		++size; // increase size
		delete [] data;
		data = new_data;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const DynArr<T> &my_arr) {
	for (int i = 0; i < my_arr.capacity; ++i)
		out << "[" << my_arr.data[i] << "]\t";
	out << std::endl;
	
	return out;
}

*/
