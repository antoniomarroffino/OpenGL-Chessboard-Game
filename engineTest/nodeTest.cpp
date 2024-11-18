#include "nodeTest.h"

NodeTest::NodeTest()
	: node_root{ new Node("root")}, node_middle{ new Node("middle")}, node_leaf{ new Node("leaf")}
{
	//id 2 -> node_root
	//id 3 -> node_middle;
	//id 4 -> node_leaf;
}

NodeTest::~NodeTest() {
	delete node_root;
	delete node_middle;
	delete node_leaf;
}

void NodeTest::test() {
	this->testCostructor();

	this->testAddChild();
	this->testGetChildren();
	this->testRemoveChild();
	this->testRemoveChildByPosition();
	this->testGetParent();
	this->testGetNumberOfChildren();

	this->testSetAndGetMatrix();
	this->testGetFinalMatrix();
	this->testFindNodeByName();
	this->testFindNodeById();
	std::cout << "All test of class Node pass" << std::endl;
}

void NodeTest::testCostructor() {
	std::cout << "Test Node::Node()" << std::endl;
	assert(this->node_root->getMatrix() == glm::mat4(1.0f));
	assert(this->node_root->getParent() == nullptr);
	assert(this->node_root->getChildren().size() == 0);
}

void NodeTest::testAddChild() {
	std::cout << "Test Node::addChild()" << std::endl;
	assert(this->node_root->addChild(nullptr) == false);
	assert(this->node_root->getNumberOfChildren() == 0);

	assert(this->node_root->addChild(this->node_middle) == true);
	assert(this->node_root->getNumberOfChildren() == 1);
	assert(this->node_middle->getParent() == this->node_root);

	assert(this->node_root->addChild(this->node_middle) == false);
	assert(this->node_root->getNumberOfChildren() == 1);

	this->node_middle->addChild(this->node_leaf);
}

void NodeTest::testGetChildren() {
	std::cout << "Test Node::getChildren()" << std::endl;
	std::vector<Node*> children = this->node_root->getChildren();

	assert(children.size() == 1);
	assert(this->node_middle == children[0]);
	assert(this->node_middle->getId() == children[0]->getId());
	assert(this->node_middle->getName() == children[0]->getName());
}

void NodeTest::testRemoveChild() {
	std::cout << "Test Node::removeChild()" << std::endl;
	assert(this->node_middle->removeChild(nullptr) == false);
	assert(this->node_middle->getNumberOfChildren() == 1);

	assert(this->node_leaf->removeChild(node_root) == false);
	assert(this->node_leaf->getNumberOfChildren() == 0);

	assert(this->node_middle->removeChild(this->node_leaf) == true);
	assert(this->node_middle->getNumberOfChildren() == 0);
	assert(this->node_leaf->getParent() == nullptr);

	this->node_middle->addChild(this->node_leaf);


	assert(this->node_root->removeChild(this->node_middle) == true);
	assert(this->node_root->getNumberOfChildren() == 0);
	assert(this->node_middle->getParent() == nullptr);
	assert(this->node_leaf->getParent() == this->node_middle);

	this->node_root->addChild(this->node_middle);
}

void NodeTest::testRemoveChildByPosition() {
	std::cout << "Test Node::removeChildByPosition()" << std::endl;
	assert(this->node_root->removeChildByPosition(1) == nullptr);
	assert(this->node_root->getNumberOfChildren() == 1);

	assert(this->node_middle->removeChildByPosition(0) == this->node_leaf);
	assert(this->node_middle->getNumberOfChildren() == 0);
	assert(this->node_leaf->getParent() == nullptr);

	this->node_middle->addChild(this->node_leaf);

	assert(this->node_root->removeChildByPosition(0) == this->node_middle);
	assert(this->node_root->getNumberOfChildren() == 0);
	assert(this->node_middle->getParent() == nullptr);
	assert(this->node_leaf->getParent() == this->node_middle);

	this->node_root->addChild(this->node_middle);
}

void NodeTest::testGetParent() {
	std::cout << "Test Node::getParent()" << std::endl;
	assert(this->node_root->getParent() == nullptr);
	assert(this->node_middle->getParent() == this->node_root);
}

void NodeTest::testGetNumberOfChildren() {
	std::cout << "Test Node::getNumberOfChildren()" << std::endl;
	assert(this->node_root->getNumberOfChildren() == 1);
	assert(this->node_leaf->getNumberOfChildren() == 0);
}

void NodeTest::testSetAndGetMatrix() {
	std::cout << "Test Node::setMatrix() && Test Node::getMatrix()" << std::endl;
	this->node_root->setMatrix(glm::mat4(2.0f));
	assert(this->node_root->getMatrix() == glm::mat4(2.0f));
}

void NodeTest::testGetFinalMatrix() {
	std::cout << "Test Node::getFinalMatrix()" << std::endl;

	glm::mat4 scale_root = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
	glm::mat4 translate_root = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f));
	glm::mat4 root_matrix = translate_root * scale_root;
	this->node_root->setMatrix(root_matrix);

	glm::mat4 rotate_middle = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 translate_middle = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 0.0f));
	glm::mat4 middle_matrix = translate_middle * rotate_middle;
	this->node_middle->setMatrix(middle_matrix);

	glm::mat4 scale_leaf = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 rotate_leaf = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translate_leaf = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 1.0f));
	glm::mat4 leaf_matrix = translate_leaf * rotate_leaf * scale_leaf;
	this->node_leaf->setMatrix(leaf_matrix);

	glm::mat4 expected_root_matrix = root_matrix;
	glm::mat4 expected_middle_matrix = root_matrix * middle_matrix;
	glm::mat4 expected_leaf_matrix = expected_middle_matrix * leaf_matrix;

	assert(this->node_root->getFinalMatrix() == expected_root_matrix);
	assert(this->node_middle->getFinalMatrix() == expected_middle_matrix);
	assert(this->node_leaf->getFinalMatrix() == expected_leaf_matrix);
}

void NodeTest::testFindNodeByName() {
	std::cout << "Test Node::findNodeByName()" << std::endl;
	assert(this->node_root->findNodeByName("ThisNodeDoesNotExist") == nullptr);
	assert(this->node_root->findNodeByName("middle") == this->node_middle);
	assert(this->node_root->findNodeByName("leaf") == this->node_leaf);
}

void NodeTest::testFindNodeById() {
	std::cout << "Test Node::findById()" << std::endl;
	assert(this->node_root->findNodeById(1000) == nullptr);
	assert(this->node_root->findNodeById(3) == this->node_middle);
	assert(this->node_root->findNodeById(4) == this->node_leaf);
}