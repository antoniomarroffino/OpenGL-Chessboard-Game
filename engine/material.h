/**
 * @file		material.h
 * @brief	Material include file
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
#include "object.h"
#include "texture.h"


 ///////////////////////
 // MAIN MATERIAL CLASS //
 ///////////////////////

 /**
  * @brief Concrete Material class
  */
class ENG_API Material : public Object {
public:
	Material(const std::string& = "defaultMaterial");
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const unsigned int parse(const char*, unsigned int&) override;
private:
	Texture* m_texture;
};