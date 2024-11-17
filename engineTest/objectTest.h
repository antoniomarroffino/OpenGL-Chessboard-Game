#pragma once

#include "test.h"

class ObjectTest : protected Test {
public:
	ObjectTest();
	void test() override;

private:
	void testGetId();
	void testGetName();
	void testSetName();

	std::shared_ptr<Object> object1;
	std::shared_ptr<Object> object2;
};
