#include <iostream>
#include <exception>

template<typename X, typename Y>
class Pair {
public:
    X first;
    Y second;

    Pair() = default; // elements can be accessed later with .first || .second
    Pair(const X& v1, const Y &v2) : first(v1), second(v2) {}
    Pair(const Pair &other) : first(other.first), second(other.second) {}
    Pair(Pair &&other) : first(std::move(other.first)), second(std::move(other.second)) {}

    Pair& operator=(const Pair &other);
    Pair& operator=(Pair &&other);

    bool operator==(const Pair &other) const;
    bool operator!=(const Pair &other) const;
    bool operator<(const Pair &other) const;
           
    void swap();

    template<typename U, typename V>
    friend std::ostream &operator<<(std::ostream &out, const Pair<U, V> &other);
};

template<typename X, typename Y>
Pair<X, Y>& Pair<X, Y>::operator=(const Pair<X, Y> &other) {
    if (this != &other) {  
        first = other.first;
        second = other.second;
    }

    return *this;
}


template<typename X, typename Y>
typename Pair<X, Y>::Pair& Pair<X, Y>::operator=(Pair<X, Y> &&other) {
    if (this != &other) {
        first = std::move(other.first);
        second = std::move(other.second);
    }

    return *this;
}

template<typename X, typename Y>
bool Pair<X, Y>::operator==(const Pair<X, Y> &other) const {
    return (first == other.first && second == other.second);

}

template<typename X, typename Y>
bool Pair<X, Y>::operator!=(const Pair<X, Y> &other) const {
    return !(*this == other);
}

template<typename X, typename Y>
bool Pair<X, Y>::operator<(const Pair<X, Y> &other) const {
    if (first == other.first) 
        return second < other.second;
    else
        return first < other.first;
}

template<typename U, typename V>
std::ostream& operator<<(std::ostream &out, const Pair<U, V> &other) {
    return out << other.first << "," << other.second;
}