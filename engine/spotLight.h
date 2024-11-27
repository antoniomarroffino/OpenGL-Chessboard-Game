/**
 * @file		spotLight.h
 * @brief	SpotLight include file
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
#include "light.h"


 ///////////////////////
 // MAIN SPOTLIGHT CLASS //
 ///////////////////////

 /**
  * @brief Concrete SpotLight class
  */
class ENG_API SpotLight : public Light {
public:
	SpotLight(const std::string&);
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
private:
};
