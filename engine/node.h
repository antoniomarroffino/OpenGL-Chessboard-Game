#pragma once

#include <vector>
#include <memory>

#include "object.h"

class Node : public Object {
public:
	Node(std::string);

	void setMatrix(glm::mat4);
	glm::mat4 getMatrix() const;
	glm::mat4 getFinalMatrix() const;
	Node* findNodeByName(std::string) const;
	std::vector<Node*> findNodesByName(std::string) const;
	Node* findById(unsigned int) const;

	void setParent(Node*);
	Node* getParent() const;
	void addChild(Node*);
	void removeChild(Node*);
	int getNumberOfChild() const;
	std::vector<Node*> getchildren() const;
private:
	glm::mat4 m_matrix;
	std::shared_ptr<Node> m_parent;
	std::vector<std::shared_ptr<Node>> m_children;
};
