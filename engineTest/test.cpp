#include "test.h"

#include "objectTest.h"
#include "nodeTest.h"

int main(void) {
	ObjectTest objectTest;
	objectTest.test();
	std::cout << std::endl;
	NodeTest nodeTest;
	nodeTest.test();

	std::cout << "\nAll test passed" << std::endl;
	return 0;
}