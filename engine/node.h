/**
 * @file		node.h
 * @brief	Node include file
 *
 * @author	Luca Fantò (C) SUPSI [luca.fanto@student.supsi.ch]
 * @author	Mattia Cainarca (C) SUPSI [mattia.cainarca@student.supsi.ch]
 * @author	Antonio Marroffino (C) SUPSI [antonio.marroffino@student.supsi.ch]
 */
#pragma once

 //////////////
 // #INCLUDE //
 //////////////

	// C/C++:
#include <vector>
#include "object.h"

 ///////////////////////
 // MAIN NODE CLASS //
 ///////////////////////

 /**
  * @brief Concrete Node class
  */
class ENG_API Node : public Object {
public:
	Node(const std::string&);
	Node(const Node&);
	virtual ~Node() = default;


	void setMatrix(const glm::mat4&);
	const glm::mat4& getMatrix() const;
	virtual const glm::mat4 getFinalMatrix() const;
	const Node* findNodeByName(const std::string&) const;
	/*const Node* findNodeById(const unsigned int&) const;*/

	Node* getMainCamera() const;

	const Node* getParent() const;
	bool addChild(Node*);
	bool removeChild(Node*);
	Node* removeChildByPosition(const unsigned int&);
	const unsigned int getNumberOfChildren() const;
	virtual const std::vector<Node*> getChildren() const;
	void setMaterial(Object*);
	const Object* getMaterial() const;
	void virtual render(const glm::mat4 & = glm::mat4(1.0f)) override;
protected:
	glm::mat4 m_matrix;
	Node* m_parent;
	std::vector<Node*> m_children;
	Object* m_material;
private:
	void setParent(Node*);
};
