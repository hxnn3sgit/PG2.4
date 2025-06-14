template <typename T>
class dyn_arr {
private:
    T *data;
    int size;
public:
    // c'tors / d'tors
    dyn_arr() : data(nullptr), size(0) {}
    ~dyn_arr();
    dyn_arr(const dyn_arr &other);
    dyn_arr(dyn_arr &&other);

    // manipulation member functions
    void prepend(const T &payload);
    void append(const T &payload);
    void delete_value(T payload);
    void delete_at_index(const int index);
    int at(const T &payload); // returns index of certain payload
    int size() { return size; }
    bool empty() { return size; }

    // operator overloading
    T operator[](int index) const; 
    void &operator[](int index);
    
};