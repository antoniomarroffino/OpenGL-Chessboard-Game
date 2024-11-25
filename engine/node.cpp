#include "node.h"
#include "camera.h"
#include <iostream>
#include <algorithm>

ENG_API Node::Node(const std::string& name) : Object(name), m_matrix{ glm::mat4(1.0f) }, m_parent{ nullptr }, m_children{ std::vector<Node*>() }, m_material{ nullptr } {}

ENG_API Node::Node(const Node& other) : Object(other), m_matrix(other.m_matrix), m_parent(other.m_parent), m_children(other.m_children), m_material{ other.m_material } {}

void ENG_API Node::setMatrix(const glm::mat4& matrix) {
	this->m_matrix = matrix;
}

const ENG_API glm::mat4& Node::getMatrix() const {
	return this->m_matrix;
}

const ENG_API glm::mat4 Node::getFinalMatrix() const {
	if (this->m_parent == nullptr)
		return this->m_matrix;
	return this->m_parent->getFinalMatrix() * this->m_matrix;
}

const ENG_API Node* Node::findNodeByName(const std::string& name) const {
	for (const auto* node : this->m_children)
		if (node->m_name == name)
			return node;

	for (const auto* node : this->m_children) {
		const Node* nodeByName = node->findNodeByName(name);
		if (nodeByName != nullptr)
			return nodeByName;
	}

	return nullptr;
}

const ENG_API Node* Node::findNodeById(const unsigned int& id) const {
	for (const auto* node : this->m_children)
		if (node->getId() == id)
			return node;

	for (const auto* node : this->m_children) {
		const Node* nodeById = node->findNodeById(id);
		if (nodeById != nullptr)
			return nodeById;
	}

	return nullptr;
}

/*void ENG_API Node::pass() {

}*/

void Node::render(const glm::mat4&){}


ENG_API Node* Node::getMainCamera() const {
	for (auto* element : this->m_children) {
		Camera* camera = dynamic_cast<Camera*>(element);
		
		if (camera != nullptr) {
			if (camera->isMainCamera()) {
				return camera;
			}
		}
		else {
			if (element != nullptr) {
				Node* childCamera = element->getMainCamera();
				if (childCamera != nullptr)
					return childCamera;
			}
		}
	}

	return nullptr;
}

void ENG_API Node::setParent(Node* parent) {
	this->m_parent = parent;
}

const ENG_API Node* Node::getParent() const {
	return this->m_parent;
}

ENG_API bool Node::addChild(Node* child) {
	if (child != nullptr && std::find(this->m_children.begin(), this->m_children.end(), child) == this->m_children.end()) {
		this->m_children.push_back(child);
		child->setParent(this);
		return true;
	}
	return false;
}

ENG_API bool Node::removeChild(Node* child) {
	if (this->m_children.size() == 0 || child == nullptr) return false;

	auto it = std::find(this->m_children.begin(), this->m_children.end(), child);
	if (it != this->m_children.end()) {
		this->m_children.erase(it);
		child->setParent(nullptr);
		return true;
	}
	return false;
}

ENG_API Node* Node::removeChildByPosition(const unsigned int& position) {
	if (position >= this->m_children.size()) return nullptr;

	Node* removedNode = this->m_children[position];
	return this->removeChild(removedNode) ? removedNode : nullptr;
}

const ENG_API unsigned int Node::getNumberOfChildren() const {
	return (unsigned int) this->m_children.size();
}

const ENG_API std::vector<Node*> Node::getChildren() const {
	std::vector<Node*> children;
	for (auto* node : this->m_children)
		children.push_back(node);
	return children;
}

void ENG_API Node::setMaterial(Object* material) {
	this->m_material = material;
}

const ENG_API Object* Node::getMaterial() const{
	return this->m_material;
}