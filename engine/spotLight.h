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
	SpotLight(const std::string& = "defaultSpotLight", const glm::vec3 & = glm::vec3(0.0f), const glm::vec3& = glm::vec3(0.0f), const float& cutoff = 45.0f);
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const unsigned int parse(const char*, unsigned int&) override;

	void setDirection(const glm::vec3&);
	const glm::vec3& getDirection() const;
	void setCutoff(const float&);
	const float& getCutoff() const;
private:
	glm::vec3 m_direction;
	float m_cutoff;
};
