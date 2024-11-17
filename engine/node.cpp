#include "node.h"

ENG_API Node::Node(const std::string& name, const std::shared_ptr<Node>& parent) : Object(name), m_parent{ parent }, m_matrix{glm::mat4(1.0f)}, m_children{std::vector<std::shared_ptr<Node>>()} {}

ENG_API Node::Node(const Node& other) : Object(other), m_parent(other.m_parent), m_matrix(other.m_matrix), m_children(other.m_children) {}

void Node::setMatrix(const glm::mat4& matrix) {
	this->m_matrix = matrix;
}

const glm::mat4& Node::getMatrix() const {
	return this->m_matrix;
}

const glm::mat4 Node::getFinalMatrix() const {
	if (this->m_parent.get() == nullptr)
		return this->m_matrix;
	return this->m_parent.get()->getFinalMatrix() * this->m_matrix;
}

const Node* Node::findNodeByName(const std::string& name) const {
	for (const auto& node : this->m_children)
		if (node.get()->m_name == name)
			return node.get();

	for (const auto& node : this->m_children) {
		const Node* nodeByName = node.get()->findNodeByName(name);
		if (nodeByName != nullptr)
			return nodeByName;
	}

	return nullptr;
}

const std::vector<Node*> Node::findNodesByName(const std::string& name) const {
	std::vector<Node*> nodeWithSameName;
	for (const auto& node : this->m_children)
		if (node.get()->m_name == name)
			nodeWithSameName.push_back(node.get());
	return nodeWithSameName;
}

const Node* Node::findById(const unsigned int& id) const {
	for (const auto& node : this->m_children)
		if (node.get()->getId() == id)
			return node.get();
	return nullptr;
}

//TODO:Dare un'occhiata
void Node::pass() {
	this->render(this->getFinalMatrix());
}

//TODO: rivedere l'implementazione
void Node::render(const glm::mat4& matrix) {
	for (const auto& element : this->m_children)
		element.get()->pass();
}

const Node* Node::getMainCamera() const {
	for (const auto& element : this->m_children) {
		//Node::Camera* cam = dynamic_cast<Node::Camera*>(element.get());
		const Node* camera = element->getCamera();
		if (camera != nullptr)
			return camera;
	}
	return nullptr;
}

const Node* Node::getCamera() const {
	return nullptr;
}

void Node::setParent(const std::shared_ptr<Node>& parent) {
	this->m_parent = parent;
}

const Node* Node::getParent() const {
	return this->m_parent.get();
}

void Node::addChild(const std::shared_ptr<Node>& child) {
	if(child != nullptr)
		this->m_children.push_back(child);
}

//Da testare
//TODO: eliminare a cascata (recuperare il node, toglierlo dal vector e fare delete, gestendo la distruzione in cascata)
void Node::removeChild(const std::shared_ptr<Node>& child) {
	if(child != nullptr)
		this->m_children.erase(this->m_children.begin() + child.get()->m_id);
}

const unsigned int Node::getNumberOfChildren() const {
	return (unsigned int) this->m_children.size();
}

const std::vector<Node*> Node::getChildren() const {
	std::vector<Node*> children;
	for (const auto& node : this->m_children)
		children.push_back(node.get());
	return children;
}