#pragma once

#include "test.h"
#include "node.h"
#include "mockList.h"
#include "mockCamera.h"
#include "material.h"


class NodeTest : public ::testing::Test {
protected:
	static Node* node_root;
	static Node* node_middle;
	static Node* node_leaf;

	static void SetUpTestSuite();

	static void TearDownTestSuite();
};