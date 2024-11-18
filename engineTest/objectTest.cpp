
#include "objectTest.h"

ObjectTest::ObjectTest() 
	: object1{ new Node("Object1") }, object2{ new Node("Object2") } {}

ObjectTest::~ObjectTest() {
	delete object1;
	delete object2;
}

void ObjectTest::test() {
	this->testGetId();
	this->testGetName();
	this->testSetName();
	std::cout << "All test of class Object pass" << std::endl;
}

void ObjectTest::testGetId() {
	std::cout << "Test Object::getId()" << std::endl;
	assert(object1->getId() == 0);
	assert(object2->getId() == 1);
}

void ObjectTest::testGetName() {
	std::cout << "Test Object::getName()" << std::endl;
	assert(object1->getName() == "Object1");
	assert(object2->getName() == "Object2");
}

void ObjectTest::testSetName() {
	std::cout << "Test Object::setName()" << std::endl;
	object2->setName("UpdatedObject2");
	assert(object2->getName() == "UpdatedObject2");
}