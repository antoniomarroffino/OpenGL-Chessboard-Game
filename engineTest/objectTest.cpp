
#include "objectTest.h"

ObjectTest::ObjectTest() 
	: object1{ std::make_shared<Node>("Object1") }, object2{ std::make_shared<Node>("Object2") } {}

void ObjectTest::test() {
	this->testGetId();
	this->testGetName();
	this->testSetName();
	std::cout << "All test of class Object pass" << std::endl;
}

void ObjectTest::testGetId() {
	std::cout << "Test Object::getId()" << std::endl;
	assert(object1.get()->getId() == 0);
	assert(object2.get()->getId() == 1);
}

void ObjectTest::testGetName() {
	std::cout << "Test Object::getName()" << std::endl;
	assert(object1.get()->getName() == "Object1");
	assert(object2.get()->getName() == "Object2");
}

void ObjectTest::testSetName() {
	std::cout << "Test Object::setName()" << std::endl;
	object2.get()->setName("UpdatedObject2");
	assert(object2.get()->getName() == "UpdatedObject2");
}