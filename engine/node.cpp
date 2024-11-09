#include "node.h"

Node::Node(std::string name)
: Object::Object(name) {}


void Node::setMatrix(glm::mat4 matrix) {
	this->m_matrix = matrix;
}

glm::mat4 Node::getMatrix() const {
	return this->m_matrix;
}

glm::mat4 Node::getFinalMatrix() const {
	if (this->m_parent.get() == nullptr)
		return this->m_matrix;
	return this->m_matrix * this->m_parent.get()->getFinalMatrix();
}

Node* Node::findNodeByName(std::string name) const {
	for (Node* node : this->getchildren())
		if (node->getName().compare(name))
			return node;

	return nullptr;
}

std::vector<Node*> Node::findNodesByName(std::string name) const {
	std::vector<Node*> nodeWithSameName;
	for (Node* node : this->getchildren())
		if (node->getName().compare(name))
			nodeWithSameName.push_back(node);
	return nodeWithSameName;
}

Node* Node::findById(unsigned int id) const {
	for (Node* node : this->getchildren())
		if (node->getId() == id)
			return node;
	return nullptr;
}

void Node::setParent(Node* parent) {
	this->m_parent = std::make_shared<Node>(parent);
}

Node* Node::getParent() const {
	return this->m_parent.get();
}

void Node::addChild(Node* child) {
	this->m_children.push_back(std::make_shared<Node>(child));
}

void Node::removeChild(Node* child) {
	this->m_children.erase(this->m_children.begin() + child->getId());
}

int Node::getNumberOfChild() const {
	return this->m_children.size();
}

std::vector<Node*> Node::getchildren() const {
	std::vector<Node*> children;
	for (auto& node : this->m_children)
		children.push_back(node.get());
	return children;
}