#include <iostream>

using namespace std;

struct node {
    int data;
    struct node *next;
    node (int d) : data(d), next(nullptr) {}
};


class int_list {
private:
    node *head;
public:
    int_list() : head(nullptr) {}
    ~int_list();
    int len();
    bool is_empty();
    void append(int payload);
    void prepend(int payload);
    friend ostream &operator<<(ostream& os, const int_list &my_list);
};

int_list::~int_list() {
    // delete the list:
	// - start at first node, save next node, delete current, go to next until everything is deleted;
	node *run = head;
	while(run) {
		node *next = run->next;
		delete run;
		run = next;
	}
}

int int_list::len() {
    // go through list and count every node
    // return len
    int count = 0;
    node *run = head;
    while (run) {
        count++;
        run = run->next;
    }
    return count;
}

bool int_list::is_empty() {
    return head == nullptr; // if head == nullptr list is empty and true is returned, otherwise false
}

void int_list::append(int payload) {
    if (head == nullptr) { // empty list
        node *new_node = new node(payload); //new_node->next already nullptr
        head = new_node;
    } else {
		node *new_node = new node(payload);
		node *run = head;

		while (run->next != nullptr) {
			run = run->next;
		}
		run->next = new_node;
	}
}

void int_list::prepend(int payload) {
	node *new_head = new node(payload);
	new_head->next = head;
	head = new_head;
}

ostream& operator<<(ostream& os, const int_list &my_list) {
	node *run = my_list.head;
    while (run) {
        os << "[" << run->data << "]-";
        run = run->next;
    }
    os << "|";
    
    return os;
}

int main() {
    
    int_list my_list;
    my_list.append(1);
    my_list.append(2);
    my_list.append(3);
   	my_list.prepend(4); 
    cout << my_list << endl;
    
    

    return 0;
}
