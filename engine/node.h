#pragma once

#include <vector>
#include <memory>

#include "object.h"
#include "list.h"

class ENG_API Node : public Object {
public:
	Node(const std::string&);
	Node(const Node&);
	virtual ~Node() = default;


	void setMatrix(const glm::mat4&);
	const glm::mat4& getMatrix() const;
	const glm::mat4 getFinalMatrix() const;
	const Node* findNodeByName(const std::string&) const;
	const Node* findNodeById(const unsigned int&) const;
	void pass();	//TODO: da testare

	const Node* getMainCamera() const;		//TODO: da testare

	const Node* getParent() const;
	bool addChild(Node*);
	bool removeChild(Node*);
	Node* removeChildByPosition(const unsigned int&);
	const unsigned int getNumberOfChildren() const;
	const std::vector<Node*> getChildren() const;
	void setMaterial(Object*);
	const Object* getMaterial() const;
	void virtual render(const glm::mat4 & = glm::mat4(1.0f)) override;
protected:
	const virtual Node* getCamera() const;

	glm::mat4 m_matrix;
	Node* m_parent;
	std::vector<Node*> m_children;
	Object* m_material;
	List& m_list;
private:
	void setParent(Node*);

	void fillList();
};
