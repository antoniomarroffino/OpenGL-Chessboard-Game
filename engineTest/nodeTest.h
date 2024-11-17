#pragma once

#include "node.h"
#include "test.h"

class NodeTest : protected Test {
public:
	NodeTest();
	void test() override;
private:
	void testCostructor();

	void testSetAndGetParent();
	void testGetNumberOfChildren();
	void testAddChild();
	void testGetChildren();
	void testRemoveChild();

	void testSetAndGetMatrix();
	void testGetFinalMatrix();
	void testFindNodeByName();

	std::shared_ptr<Node> node_root;
	std::shared_ptr<Node> node_middle;
	std::shared_ptr<Node> node_leaf;
};
