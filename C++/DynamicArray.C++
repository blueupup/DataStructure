#include <iostream>
using namespace std;

template <class T>
class DynamicArray {
public:
    T* data;
    int size;

public:
    DynamicArray(int s) {
        size = s;
        data = new T[size];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void set(int index, T value) {
        if (index >= 0 && index < size)
            data[index] = value;
        else
            cout << "Index out of range!" << endl;
    }

    get(int index) const {
        if (index >= 0 && index < size)
            return data[index];
        else {
            cout << "Index out of range!" << endl;
            return T();
        }
    }

    void print() const {
        cout << "Elements of the array are: ";
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }

    int getSize() const {
        return size;
    }
};