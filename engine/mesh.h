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


 ///////////////////////
 // MAIN MESH CLASS //
 ///////////////////////

 /**
  * @brief Concrete Mesh class
  */
class ENG_API Mesh : public Node {
public:
	Mesh(const std::string&, const std::vector<glm::vec3>&);
	void render(const glm::mat4&) override;
private:
	std::vector<glm::vec3> m_vertices;
};