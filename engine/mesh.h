/**
 * @file		mesh.h
 * @brief	Mesh include file
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
#include "node.h"
#include <glm/gtc/packing.hpp>
#include <memory>


 ///////////////////////
 // MAIN MESH CLASS //
 ///////////////////////

 /**
  * @brief Concrete Mesh class
  */
class ENG_API Mesh : public Node {
public:
	Mesh(const std::string& = "defaultMesh");
	Mesh(const Mesh&);
	Mesh& operator=(const Mesh&) = delete;
	void render(const glm::mat4&) override;
	const unsigned int parse(const char*, unsigned int&) override;
	Node* clone() const override;

	std::vector<glm::vec3> getVertices();

	~Mesh();

private:

	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
};