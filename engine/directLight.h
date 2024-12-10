/**
 * @file		directLight.h
 * @brief	DirectLight include file
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
 // MAIN DIRECTLIGHT CLASS //
 ///////////////////////

 /**
  * @brief Concrete DirectLight class
  */
class ENG_API DirectLight : public Light {
public:
	DirectLight(const std::string& = "defaultDirectLight", const glm::vec3& = glm::vec3(0.0f));
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;

	void setPosition(const glm::vec3&) override;
private:
};
