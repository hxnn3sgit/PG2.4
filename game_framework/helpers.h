// helpers.h
// for own STL Datastructures like dynamic arrays and stuff

<template T>
class my_vector {
private:
	T* data;
	int size; // int because of better handle
public:
	my_vector() : data(nullptr), size(0);
	my_vector(int size);
	// constructor with initializer list?
	~my_vector();
	void push_back(T x);
	void pop_back();
   	friend std::ostream &operator<<(std::ostream &os, const my_vector & v);
	// subscript operator[]
}
