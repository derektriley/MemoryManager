#include "MemoryManager.h"

class MineSweeperMemory : public MemoryManager {
public:
	MineSweeperMemory();
	int readMines();
	void writeMines(int value);
};