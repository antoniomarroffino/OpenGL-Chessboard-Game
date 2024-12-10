/**
 * @file		texture.h
 * @brief	Texture include file
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


 ///////////////////////
 // MAIN TEXTURE CLASS //
 ///////////////////////

 /**
  * @brief Concrete Texture class
  */
class ENG_API Texture : public Object {
public:
	Texture(const std::string&);
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;

private:
	unsigned int m_textureId;

};