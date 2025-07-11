#include <vector>

class GarbageCollector;

class GarbageCollector {
private:
	static std::vector<GarbageCollector*> garbage;

protected:
	bool shouldFree = false;

public:
	virtual ~GarbageCollector() = default;

	/**
	 * @brief Sets shouldFree to true and adds this object to the garbage vector.
	 */
	void collect();
	void cancelCollection();

	bool getShouldFree();

	/**
	 * @brief clears garbage vector that contains all the objects to be freed
	 */
	static void clearGarbage();
};