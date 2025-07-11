#include <iostream>
#include <cstdlib>
#include <stdint.h>

#ifdef _MSC_VER
#include <windows.h>
#endif

void* operator new(size_t size) {
#ifdef _MSC_VER
    char buf[64];
    sprintf_s(buf, "Allocated %zu bytes\n", size);
    OutputDebugStringA(buf);
#else
    std::cout << "Allocated " << size << " bytes\n";
#endif
    return malloc(size);
}

#ifdef _MSC_VER
void* operator new[](size_t size) {
    std::cout << "Allocated array of " << size << " bytes\n";
    return malloc(size);
}

void* operator new(size_t size, const std::nothrow_t&) noexcept {
    std::cout << "Allocated (nothrow) " << size << " bytes\n";
    return malloc(size);
}

void operator delete(void* pObject, size_t size) noexcept {
    free(pObject);
    std::cout << "Deallocated " << size << " bytes\n";
}

void operator delete[](void* pObject) noexcept {
    free(pObject);
    std::cout << "Deallocated an array object\n";
}

void operator delete[](void* pObject, size_t size) noexcept {
    free(pObject);
    std::cout << "Deallocated array of " << size << " bytes\n";
}
#else
void operator delete(void* pObject) {
    free(pObject);
    std::cout << "Deallocated an object\n";
}
#endif

template<typename T, typename Size = size_t>
class List {
public:
    List() {}

    ~List() {
        clear();
    }
    
    void clear() {
        for (Size i = 0; i < size; ++i)
            delete pArray[i];

        size = 0;
        delete[] pArray;
        pArray = nullptr;
    }

    void push_back(const T& object) {
        T** pNewArray = new T*[size+1];
        for (Size i = 0; i < size; ++i)
            pNewArray[i] = pArray[i];

        if (pArray)
            delete[] pArray;
        pArray = pNewArray;

        pArray[size] = new T(object);
        ++size;
    }
    
    T* operator[](Size index) {
        if (index >= size)
            return nullptr;
        else
            return pArray[index];
    }

    T** pArray = nullptr;
    Size size = 0;
};

int main()
{
    List<int, uint8_t> integers;
    integers.push_back(10);
    integers.push_back(-25);
    integers.push_back(69420);
    integers.push_back(420569);
    
    for (decltype(integers.size) i = 0; i < integers.size; ++i) {
        std::cout << *integers[i] << " ";
    }

    std::cout << "\nHeap: " << integers.size*sizeof(int) << "\n";

    return 0;
}
