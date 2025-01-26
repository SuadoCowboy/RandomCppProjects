#include <iostream>

/*
// https://www.youtube.com/watch?v=sLlGEUO_EGE
The implementation of the de-allocation is based on which complier you are using, 
for clang++ you can pass the flag -fsized-deallocation as it is not implemented yet 
for GNU GCC g++ its supported by default
*/

size_t memoryUsage = 0;
void* operator new(size_t size) {
    memoryUsage += size;
    std::cout << "Allocated " << size << " bytes\n";
    return malloc(size);
}

void* operator new[](size_t size) {
    memoryUsage += size;
    std::cout << "Allocated " << size << " bytes\n";
    return malloc(size);
}

void deallocate(void* pMemory, size_t size) {
    free(pMemory);
    std::cout << "Deallocated " << size << " bytes\n";
    memoryUsage -= size;
}

void checkMemory() {
    if (memoryUsage == 0)
        return;
    
    std::cout << "WARNING: Possible memory leak!\nMemory usage: " << memoryUsage << " bytes\n";
}

int main()
{
    char* sayGex = new char[6];
    sayGex[0] = 'a';
    sayGex[1] = 'b';
    sayGex[2] = 'c';
    sayGex[3] = 'd';
    sayGex[4] = 'e';
    sayGex[5] = 'f';
    
    std::cout << sayGex << "\n";

    deallocate(sayGex, 6);
    checkMemory();
    return 0;
}