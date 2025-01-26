#include <iostream>

void* operator new(size_t size) {
    std::cout << "Allocated " << size << " bytes\n";
    return malloc(size);
}

void operator delete(void* pObject) {
    free(pObject);
    std::cout << "Deallocated an object\n";
}

template<typename T>
class List {
public:
    List() {}

    ~List() {
        clear();
    }
    
    void clear() {
        for (size_t i = 0; i < size; ++i) {
            delete pData[i];
        }
        size = 0;
        delete[] pData;
        pData = nullptr;
    }

    void push_back(const T& object) {
        T** pNewData = new T*[size+1];
        for (size_t i = 0; i < size; ++i)
            pNewData[i] = pData[i];

        delete[] pData;
        pData = pNewData;

        pData[size] = new T(object);
        ++size;
    }
    
    T* operator[](size_t index) {
        if (index >= size)
            return nullptr;
        else
            return pData[index];
    }

    T** pData = nullptr;
    size_t size = 0;
};

int main()
{
    List<int> integers;
    integers.push_back(10);
    integers.push_back(25);
    integers.push_back(69420);
    integers.push_back(420569);
    
    for (size_t i = 0; i < integers.size; ++i) {
        std::cout << *integers[i] << " ";
    }
    
    std::cout << "\nHeap: " << integers.size*sizeof(int) << "\n";

    return 0;
}
