#pragma once

#include <vector>
#include <memory>

#include "object.h"

class Node : public Object {
public:
	Node(const std::string&);
	Node(const Node&);

	void setMatrix(const glm::mat4&);
	const glm::mat4& getMatrix() const;
	const glm::mat4 getFinalMatrix() const;
	const Node* findNodeByName(const std::string&) const;
	const std::vector<Node*> findNodesByName(const std::string&) const;
	const Node* findById(const unsigned int&) const;
	void virtual render(const glm::mat4& = glm::mat4(1.0f)) override;

	const Node* getMainCamera() const;

	void setParent(Node*);
	const Node* getParent() const;
	void addChild(Node*);
	void removeChild(Node*);
	const unsigned int getNumberOfChildren() const;
	const std::vector<Node*> getchildren() const;
protected:
	const virtual Node* getCamera() const;

	glm::mat4 m_matrix;
	std::shared_ptr<Node> m_parent;
	std::vector<std::shared_ptr<Node>> m_children;
};
