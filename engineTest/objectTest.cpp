
#include "objectTest.h"

Object* ObjectTest::object1 = nullptr;
Object* ObjectTest::object2 = nullptr;

void ObjectTest::SetUpTestSuite() {
	object1 = new Node("Object1");
	object2 = new Node("Object2");
}

void ObjectTest::TearDownTestSuite() {
	delete object1;
	delete object2;
}
/*
TEST_F(ObjectTest, GetId) {
	ASSERT_EQ(0, object1->getId());
	ASSERT_EQ(1, object2->getId());
}*/

TEST_F(ObjectTest, GetName) {
	EXPECT_EQ("Object1", object1->getName());
	EXPECT_EQ("Object2", object2->getName());
}

TEST_F(ObjectTest, SetName) {
	object2->setName("UpdatedObject2");
	EXPECT_EQ("UpdatedObject2", object2->getName());
}