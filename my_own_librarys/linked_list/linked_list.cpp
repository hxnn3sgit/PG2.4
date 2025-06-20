#include "linked_list.h"

template<typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T> &other); /* {
    out << "Linked List:" << std::endl;
    Node *run = other.head;
    while (run) {
        out << "--[" << run->data << "]--";
    }
    out << "|" << std::endl;
    
    return out;
} */