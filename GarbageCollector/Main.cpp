#include <iostream>

#include "GarbageCollector.h"

class Object : public GarbageCollector {
public:
	int value = 0;

	Object(int value = 420) : value(value) {
		std::cout << "Object created. (value = " << value << ")\n";
	}

	~Object() {
		std::cout << "Object destroyed." << std::endl;
		*this = {};
	}
};

int main() {
	Object* pObject = new Object(69420);

	pObject->collect();
	if (pObject->getShouldFree()) {
		std::cout << "Object is marked for collection.\n";
	}

	std::cout << pObject->value << '\n';
	GarbageCollector::clearGarbage();
	std::cout << pObject->value << '\n';

	return 0;
}