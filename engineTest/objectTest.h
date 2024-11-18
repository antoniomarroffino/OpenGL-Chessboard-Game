#pragma once

#include "test.h"

class ObjectTest : protected Test {
public:
	ObjectTest();
	~ObjectTest();
	void test() override;

private:
	void testGetId();
	void testGetName();
	void testSetName();

	Object* object1;
	Object* object2;
};
