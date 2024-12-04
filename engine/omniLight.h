/**
 * @file		omniLight.h
 * @brief	OmniLight include file
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
 // MAIN OMNILIGHT CLASS //
 ///////////////////////

 /**
  * @brief Concrete OmniLight class
  */
class ENG_API OmniLight : public Light {
public:
	OmniLight(const std::string& = "defaultOmniLight", const glm::vec3& = glm::vec3(0.0f));
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const unsigned int parse(const char*, unsigned int&) override;

	const float& getCutoff() const;
private:
	float m_cutoff;
};
