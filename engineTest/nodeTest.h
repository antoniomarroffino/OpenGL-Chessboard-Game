#pragma once

#include "test.h"
#include "node.h"
#include "material.h"


class NodeTest : public ::testing::Test {
protected:
	// Puntatori condivisi tra i test
	static Node* node_root;
	static Node* node_middle;
	static Node* node_leaf;

	// Setup globale della suite (eseguito una sola volta)
	static void SetUpTestSuite();

	// TearDown globale della suite (eseguito una sola volta)
	static void TearDownTestSuite();
};

/*
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
*/