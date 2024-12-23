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
	virtual void render(const glm::mat4 & = glm::mat4(1.0f)) override;
	const virtual unsigned int parse(const char*, unsigned int&) override;
	virtual Node* clone() const override = 0;

	virtual void setPosition(const glm::vec3&);
	const glm::vec4& getPosition() const;
	static void resetLightCounter();
protected:
	Light(const std::string&, const glm::vec4&);
	Light(const Light&);
	Light& operator=(const Light&) = delete;

	glm::vec4 m_position;
	Material* m_lightMaterial;
	static unsigned int maxNumberOfActiveLights;
	static unsigned int lightActiveCounter;
};