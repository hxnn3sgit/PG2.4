#include <iostream>


class Buffer {
private:
    int* data;
    size_t size;
public:
	Buffer() : data(nullptr), size(0) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    Buffer(size_t sz) : data(new int[sz]), size(sz) { std::cout << __PRETTY_FUNCTION__ << std::endl;}
    ~Buffer() { delete [] data; std::cout << __PRETTY_FUNCTION__ << std::endl; }

    // Copy Constructor
    Buffer(const Buffer& other) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		data = new int[other.size];
		size = other.size;

		for (int i = 0; i < size; ++i) {
			data[i] = other.data[i];
		}
	}

    // Move Constructor
    Buffer(Buffer&& other) noexcept {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		data = other.data;
		size = other.size;
		other.data = nullptr;
		other.size = 0;
	}

    // Copy Assignment Operator
    Buffer& operator=(const Buffer& other) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		if (this != &other) {
			delete [] data;	
			size = other.size;
			data = new int[size];

			for (int i = 0; i < size; ++i)
				data[i] = other.data[i];
		}

		return *this;
	}
    // Move Assignment Operator
    Buffer& operator=(Buffer&& other) noexcept {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		
		if (this != &other) {	
			delete [] data;
			size = other.size;
			data = other.data;
			other.data = nullptr;
			other.size = 0;
		}

		return *this;
	}

	int operator[](const int index) const {
		return data[index];
	}

    friend std::ostream& operator<<(std::ostream&  out, const Buffer &buf);
};

std::ostream& operator<<(std::ostream& out, const Buffer &buf) {
	out << "buffer:" << std::endl;
	for (int i = 0; i < buf.size; ++i)
		out << buf.data[i] << "\t";
	out << std::endl;
	return out;
}

class AdvancedBuffer : public Buffer {
private:
    std::string* labels;
    size_t label_count;
public:
    AdvancedBuffer() : Buffer(), labels(nullptr), label_count(0) { std::cout << __PRETTY_FUNCTION__ << std::endl; } // default
    AdvancedBuffer(size_t size, size_t label_count) : Buffer(size), labels(new std::string[label_count]), label_count(label_count) { std::cout << __PRETTY_FUNCTION__ << std::endl; }// param
    ~AdvancedBuffer() { delete [] labels; std::cout << __PRETTY_FUNCTION__ << std::endl; }; // dtor

    AdvancedBuffer(const AdvancedBuffer& other) : Buffer(other) {            // cctor
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		labels = new std::string[other.label_count];
		label_count = other.label_count;
		for (int i = 0; i < label_count; ++i)
			labels[i] = other.labels[i];
	}
	AdvancedBuffer(AdvancedBuffer&& other) noexcept : Buffer(std::move(other)) { // move ctor
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		//delete [] labels;
		labels = other.labels;
		label_count = other.label_count;
		other.labels = nullptr;
		other.label_count = 0;
	}        
    AdvancedBuffer& operator=(const AdvancedBuffer& other) {  // copy =
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		if (this != &other) {
			Buffer::operator=(other);
			delete [] labels;
			label_count = other.label_count;
			labels = new std::string[label_count];
			for (int i = 0; i < label_count; ++i)
				labels[i] = other.labels[i];
		}
		return *this;
	}
	AdvancedBuffer& operator=(AdvancedBuffer&& other) noexcept { // move =
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		if (this != &other) {
			Buffer::operator=(std::move(other));
			delete [] labels;
			label_count = other.label_count;
			labels = other.labels;
			other.labels= nullptr;
			other.label_count = 0;
		}
		return *this;
	}

	std::string operator[](const int index) const {
		return labels[index];
	}

     friend std::ostream& operator<<(std::ostream& out, const AdvancedBuffer &adv_buf);
};

std::ostream& operator<<(std::ostream& out, const AdvancedBuffer &adv_buf) {
	out << "advanced buf:" << std::endl;
	for (int i = 0; i < adv_buf.label_count; ++i)
		out << adv_buf.labels[i] << "\t";
	out << std::endl;

	return out;
}


int main() {
	Buffer b1; //default ctor: nullptr, size = 0;
	Buffer b2(10); // parameterized ctor: data has space for 10 ints
	Buffer b3 = b2; // cctor
	Buffer b4(b2); // cctor 
	Buffer b5(std::move(b1)); // move ctor
		
    AdvancedBuffer ab1(10, 3);
    AdvancedBuffer ab2 = ab1;
    AdvancedBuffer ab3(std::move(ab1));
    ab2 = ab3;
    ab3 = std::move(ab2);


	std::cout << b2 << std::endl;
	std::cout << ab1 << std::endl;

	return 0;
}
