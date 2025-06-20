#pragma once

#include <iostream>

template<typename T>
class LinkedList {
	struct Node {
		T value;
		Node *next;
		Node(const T &value) : value(value), next(nullptr) {}
	};
	Node *m_Head;
public:
	LinkedList() : m_Head(nullptr) {}
	~LinkedList();
	LinkedList(const LinkedList &other);
	LinkedList(LinkedList &&other);
	LinkedList& operator=(const LinkedList &other);
	LinkedList& operator=(LinkedList &&other);

	void append(const T &value);
	void prepend(const T &value);
	void popFront();
	bool empty() const;
	size_t size() const;

	void insertAt(size_t index, const T &value);
	void deleteAt(size_t index);
	
	class Iterator {
	private:
		Node *m_Current;
	public:
		Iterator(Node* start) : m_Current(start) {}
		
		T& operator*() const;
		T* operator->() const;
		Iterator& operator++(); 			// prefix increment
		Iterator operator++(int);			// postfix increment
		Iterator& operator--() = delete; 	// prefix decrement
		Iterator operator--(int) = delete;	// postfix decrement
		bool operator==(const Iterator &other) const;
		bool operator!=(const Iterator &other) const;	
	};

	Iterator begin();
	Iterator end();
	Iterator begin() const;
	Iterator end() const;

	template<typename U>
	friend std::ostream& operator<<(std::ostream &out, const LinkedList<U> &myList);

};

template<typename T>
LinkedList<T>::~LinkedList() {
	// delete node by node
}

// C C'tor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList &other) {
	// copy node by node
}

//Move C'tor
template<typename T>
LinkedList<T>::LinkedList(LinkedList &&other) {
	// move only head pointer to new memory location
}


// copy assignment op
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &other) {
	// same as cctor
}

// move assignment op
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> &&other) {
	// same as move ctor
}

template<typename T>
void LinkedList<T>::append(const T &value) {
	/* logic for appending:
		- check if list is empty, if yes, value is  new head
		- else: go to the last list node, set the next pointer from the last list node to 
			    newly created node
		
	*/
	Node *new_node = new Node(value); // is creating a new node with value(value) and next(nullptr)
	if (empty()) {
		m_Head = new_node;
	} else {
		Node *run = m_Head;
		while (run->next != nullptr)
			run = run ->next;
		
		run->next = new_node;
		// run doesn't have to be deleted, it would delete the node it is pointed to
	}
}

template <typename T>
void LinkedList<T>::prepend(const T &value) {
	Node *new_node = new Node(value);
	if (empty()) {
		m_Head = new_node;
	} else {
		new_node->next = m_Head;
		m_Head = new_node;
	}
}

template <typename T>
void LinkedList<T>::popFront() {
	try {
		deleteAt(0);
	} catch (std::runtime_error &e) {
		std::cerr << "Exception while trying to pop front: " << e.what() << std::endl;
	}
}

template<typename T>
bool LinkedList<T>::empty() const {
	if (size() == 0)
		return true;
	else
		return false;
}

template<typename T>
size_t LinkedList<T>::size() const {
	if (m_Head == nullptr)
		return 0;
	else {
		Node *run = m_Head;
		size_t counter = 0;
		while (run) {
			counter++;
			run = run->next;
		}
		return counter;
	}
}

template<typename T>
void LinkedList<T>::insertAt(size_t index, const T &value) {
	/*
	index 0 is first element
	some checks are needed:
	- is index not out of bounds?
	- if index = 0 -> prepend
	- if index = size -> append
	if list is empty, it doesn't matter, value is first element
	*/

	if (index > size()) {
		throw std::out_of_range("index below zero or too large");
	}

	Node *new_node = new Node(value);
	if (empty()) {
		throw std::runtime_error("list is empty, cant be inserted at index");
	}
	if (index == 0) {
		prepend(value);
		return;
	} else if (index == size()) {
		append(value);
		return;
	} else {
		Node *run = m_Head;

		for (int i = 0; i < (index - 1); ++i) { // go to node before insertion
			run = run->next;
		}
		new_node->next = run->next;
		run->next = new_node;

	}
}

template<typename T>
void LinkedList<T>::deleteAt(size_t index) {

}

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T> &other) {
    out << "Linked List:" << std::endl;
    typename LinkedList<T>::Node *run = other.m_Head;
    while (run) {
        out << "--[" << run->value << "]--";
		run = run->next;
    }
    out << "|" << std::endl;
    
    return out;
}


// ITERATORS:

template<typename T>
T& LinkedList<T>::Iterator::operator*() const { return *m_Current->value }

template<typename T>
T* LinkedList<T>::Iterator::operator->() const { return m_Current->value; }

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() { 	// prefix increment
	if (m_Current->next != nullptr) {
		m_Current = m_Current->next;
		return m_Current;
	} else {
		// ist schon ende der liste, keine ahnung was dann
	}
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {	// postfix increment
	Iterator before = m_Current;
	m_Current = m_Current->next;
	return before;
}

template<typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator &other) const {
	return m_Current == other.m_Current;
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator &other) const {
	return !(this == other);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
	return LinkedList<T>::m_Head;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const {
	return LinkedList<T>::m_Head;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
	Node *run = m_Head;
	while (run)
		run = run->next;

	return run;
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const {
	if (m_Head != nullptr) {
		Node *run = m_Head;
		while (run)
			run = run->next;

		return Iterator(run->next);
	} else
		return Iterator(nullptr);
}