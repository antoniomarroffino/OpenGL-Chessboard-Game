#pragma once

#include "node.h"
#include "material.h"
#include "test.h"

class NodeTest : protected Test {
public:
	NodeTest();
	~NodeTest();
	void test() override;
private:
	void testCostructor();

	void testAddChild();
	void testGetChildren();
	void testRemoveChild();
	void testRemoveChildByPosition();
	void testGetParent();
	void testGetNumberOfChildren();
	void testSetAndGetMaterial();


	void testSetAndGetMatrix();
	void testGetFinalMatrix();
	void testFindNodeByName();
	void testFindNodeById();

	Node* node_root;
	Node* node_middle;
	Node* node_leaf;
};
