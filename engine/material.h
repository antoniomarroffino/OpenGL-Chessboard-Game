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
#include <map>


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

	void setAlpha(const float&);
	const float& getAlpha() const;
	void setEmission(const glm::vec3&);
	const glm::vec4& getEmission() const;
	void setAmbient(const glm::vec3&);
	const glm::vec4& getAmbient() const;
	void setSpecular(const glm::vec3&);
	const glm::vec4& getSpecular() const;
	void setDiffuse(const glm::vec3&);
	const glm::vec4& getDiffuse() const;
	void setShininess(const float&);
	const float& getShininess() const;
	void setTexture(Texture*);
	const Texture* getTexture() const;
private:
	Texture* getTexture(const std::string&) const;
	static std::map<const std::string&, Texture*> m_texturesMap;

	float m_alpha;
	glm::vec4 m_emission;
	glm::vec4 m_ambient;
	glm::vec4 m_specular;
	glm::vec4 m_diffuse;
	float m_shininess;
	Texture* m_texture;
};