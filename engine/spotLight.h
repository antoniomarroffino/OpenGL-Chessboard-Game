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
	SpotLight(const std::string& = "defaultSpotLight", const glm::vec3 & = glm::vec3(1.0f), const glm::vec3& = glm::vec3(0.0f), const float& = 45.0f, const float& = 1.0f);
	SpotLight(const SpotLight&);
	SpotLight& operator=(const SpotLight&) = delete;
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const unsigned int parse(const char*, unsigned int&) override;
	Node* clone() const override;

	void setDirection(const glm::vec3&);
	const glm::vec3& getDirection() const;
	void setCutoff(const float&);
	const float& getCutoff() const;
	void setSpotExponent(const float&);
	const float& getSpotExponent() const;
private:
	glm::vec3 m_direction;
	float m_cutoff;
	float m_spotExponent;
};
