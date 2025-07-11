#include "GarbageCollector.h"

std::vector<GarbageCollector*> GarbageCollector::garbage = {};

void GarbageCollector::collect()
{
	if (shouldFree)
		return;

	shouldFree = true;
	garbage.push_back(this);
}

void GarbageCollector::cancelCollection()
{
	if (!shouldFree)
		return;

	shouldFree = false;
	for (auto it = garbage.begin(); it != garbage.end(); ++it) {
		if (*it == this) {
			garbage.erase(it);
			break;
		}
	}
}

bool GarbageCollector::getShouldFree() { return shouldFree; }

void GarbageCollector::clearGarbage() {
	for (GarbageCollector* g : garbage)
		delete g;

    garbage.clear();
}