#include <iostream>
#include <vector>

int main() {
    int *my_arr = new int[3];

    my_arr[0] = 1;
    my_arr[1] = 2;
    my_arr[2] = 3;

    int *ptr = my_arr + 2;

    for (int i = 0; i < 3; ++i) {
        std::cout << *ptr << std::endl;
        ptr--;
    }

    delete [] my_arr;

    return 0;
}

/*
#include <iostream>

int main() {
    int *my_arr = new int[3];

    my_arr[0] = 1;
    my_arr[1] = 2;
    my_arr[2] = 3;

    // Zeiger auf das letzte Element setzen
    int *ptr = my_arr + 2;

    for (int i = 0; i < 3; ++i) {
        std::cout << *ptr << std::endl;
        ptr--;
    }

    delete[] my_arr; // Wichtig: Speicher wieder freigeben

    return 0;
} */