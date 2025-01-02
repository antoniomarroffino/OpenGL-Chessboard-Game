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
#include "material.h"
#include "notificationService.h"

 ///////////////////////
 // MAIN NODE CLASS //
 ///////////////////////

 /**
  * @brief Concrete Node class
  */
class ENG_API Node : public Object {
public:
	Node(const std::string& = "defaultNode");
	virtual ~Node();
	Node& operator=(const Node&) = delete;


	void setMatrix(const glm::mat4&);
	const glm::mat4& getMatrix() const;
	virtual const glm::mat4 getFinalMatrix() const;
	const Node* findNodeByName(const std::string&) const;

	Node* getMainCamera() const;

	const Node* getParent() const;
	bool addChild(Node*);
	bool removeChild(Node*);
	Node* removeChildByPosition(const unsigned int&);
	const unsigned int getNumberOfChildren() const;
	virtual const std::vector<Node*> getChildren() const;
	void setMaterial(Material*);
	Material* getMaterial() const;
	void virtual render(const glm::mat4 & = glm::mat4(1.0f)) override { std::cout << this->getName() << std::endl; };
	const virtual unsigned int parse(const char*, unsigned int&) override;
	virtual Node* clone() const;
	void setEnableLighting(const bool&);

protected:
	Node(const Node&);
	
	virtual void recursiveClone(Node*) const;
	void recursiveNotifyChangeMatrix();

	bool isEnableLighting() const;

	glm::mat4 m_matrix;
	Node* m_parent;
	std::vector<Node*> m_children;
	Material* m_material;
	bool m_enableLighting;
private:
	void setParent(Node*);

	NotificationService& m_notificationService;
	bool m_isMatrixParsed;
};
