#define GLM_ENABLE_EXPERIMENTAL
#include "nodeTest.h"
#include "glm/gtx/string_cast.hpp"

NodeTest::NodeTest()
	: node_root{ std::make_shared<Node>("root") }, node_middle{ std::make_shared<Node>("middle", node_root) }, node_leaf{ std::make_shared<Node>("leaf", node_middle) } {}

void NodeTest::test() {
	this->testCostructor();

	this->testSetAndGetParent();
	this->testGetNumberOfChildren();
	this->testAddChild();
	this->testGetChildren();
	//this->testRemoveChild();

	this->testSetAndGetMatrix();
	this->testGetFinalMatrix();
	this->testFindNodeByName();
	std::cout << "All test of class Node pass" << std::endl;
}

void NodeTest::testCostructor() {
	std::cout << "Test Node::Node()" << std::endl;
	assert(this->node_root.get()->getMatrix() == glm::mat4(1.0f));
	assert(this->node_root.get()->getParent() == nullptr);
	assert(this->node_root.get()->getChildren().size() == 0);

	assert(this->node_root.get() == this->node_middle.get()->getParent());
	assert(this->node_root.get()->getId() == this->node_middle.get()->getParent()->getId());
	assert(this->node_root.get()->getName() == this->node_middle.get()->getParent()->getName());

	assert(this->node_middle.get() == this->node_leaf.get()->getParent());
	assert(this->node_middle.get()->getId() == this->node_leaf.get()->getParent()->getId());
	assert(this->node_middle.get()->getName() == this->node_leaf.get()->getParent()->getName());
}

void NodeTest::testSetAndGetMatrix() {
	std::cout << "Test Node::setMatrix() && Test Node::getMatrix()" << std::endl;
	this->node_root.get()->setMatrix(glm::mat4(2.0f));
	assert(this->node_root.get()->getMatrix() == glm::mat4(2.0f));
}

void NodeTest::testSetAndGetParent() {
	std::cout << "Test Node::setParent() && Test Node::getParent()" << std::endl;
	std::shared_ptr<Node> tempNode = std::make_shared<Node>(Node("tempNode"));
	this->node_root.get()->setParent(tempNode);
	assert(this->node_root.get()->getParent()->getName() == tempNode->getName());
	assert(this->node_root.get()->getParent()->getId() == tempNode->getId());
	assert(this->node_root.get()->getParent()->getMatrix() == tempNode->getMatrix());

	this->node_root.get()->setParent(nullptr);
	assert(this->node_root.get()->getParent() == nullptr);
}

void NodeTest::testGetNumberOfChildren() {
	std::cout << "Test Node::getNumberOfChildren()" << std::endl;
	assert(this->node_root.get()->getNumberOfChildren() == 0);
}

void NodeTest::testAddChild() {
	std::cout << "Test Node::addChild()" << std::endl;
	this->node_root.get()->addChild(nullptr);
	assert(this->node_root.get()->getNumberOfChildren() == 0);

	this->node_root.get()->addChild(this->node_middle);
	assert(this->node_root.get()->getNumberOfChildren() == 1);

	this->node_middle.get()->addChild(this->node_leaf);
}

void NodeTest::testGetChildren() {
	std::cout << "Test Node::getChildren()" << std::endl;
	std::vector<Node*> children = this->node_root.get()->getChildren();

	assert(children.size() == 1);
	assert(this->node_middle.get() == children[0]);
	assert(this->node_middle.get()->getId() == children[0]->getId());
	assert(this->node_middle.get()->getName() == children[0]->getName());
}

//TODO: Da completare (prima finire logica del metodo concreto)
void NodeTest::testRemoveChild() {

}

void NodeTest::testGetFinalMatrix() {
	std::cout << "Test Node::getFinalMatrix()" << std::endl;
	this->node_root.get()->setMatrix(glm::mat4(2.0f));
	this->node_middle.get()->setMatrix(glm::mat4(3.0f));
	this->node_leaf.get()->setMatrix(glm::mat4(4.0f));

	assert(this->node_root.get()->getFinalMatrix() == glm::mat4(2.0f));
	assert(this->node_middle.get()->getFinalMatrix() == (glm::mat4(2.0f) * glm::mat4(3.0f)));
	assert(this->node_leaf.get()->getFinalMatrix() == (glm::mat4(2.0f) * glm::mat4(3.0f) * glm::mat4(4.0f)));
}

void NodeTest::testFindNodeByName() {
	std::cout << "Test Node::findNodeByName()" << std::endl;
	assert(this->node_root.get()->findNodeByName("ThisNodeDoesNotExist") == nullptr);
	assert(this->node_root.get()->findNodeByName("middle") == this->node_middle.get());
	assert(this->node_root.get()->findNodeByName("leaf") == this->node_leaf.get());
}