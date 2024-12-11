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
#include <memory>


 ///////////////////////
 // MAIN TEXTURE CLASS //
 ///////////////////////

 /**
  * @brief Concrete Texture class
  */
class ENG_API Texture : public Object {
public:
	Texture(const std::string&);
	~Texture();
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const unsigned int parse(const char*, unsigned int&) override;

private:
	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
};