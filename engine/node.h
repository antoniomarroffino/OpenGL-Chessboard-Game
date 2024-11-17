#pragma once

#include <vector>
#include <memory>

#include "object.h"

class ENG_API Node : public Object {
public:
	Node(const std::string&, const std::shared_ptr<Node>& = nullptr);
	Node(const Node&);

	void setMatrix(const glm::mat4&);
	const glm::mat4& getMatrix() const;
	const glm::mat4 getFinalMatrix() const;
	const Node* findNodeByName(const std::string&) const;
	const std::vector<Node*> findNodesByName(const std::string&) const;
	const Node* findById(const unsigned int&) const;
	void pass();

	const Node* getMainCamera() const;

	void setParent(const std::shared_ptr<Node>&);
	const Node* getParent() const;
	void addChild(const std::shared_ptr<Node>&);
	void removeChild(const std::shared_ptr<Node>&);
	const unsigned int getNumberOfChildren() const;
	const std::vector<Node*> getChildren() const;
protected:
	void virtual render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const virtual Node* getCamera() const;

	glm::mat4 m_matrix;
	std::shared_ptr<Node> m_parent;
	std::vector<std::shared_ptr<Node>> m_children;
};
