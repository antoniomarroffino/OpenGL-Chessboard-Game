/**
 * @file		light.h
 * @brief	Light include file
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
 // MAIN LIGHT CLASS //
 ///////////////////////

 /**
  * @brief Abstract base Light class
  */
class ENG_API Light : public Node {
public:
	virtual void render(const glm::mat4 & = glm::mat4(1.0f)) override = 0;
	const virtual unsigned int parse(const char*, unsigned int&) override = 0;

protected:
	Light(const std::string&);
	virtual ~Light() = default;
};