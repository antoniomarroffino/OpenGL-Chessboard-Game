#include "material.h"
#include <GL/freeglut.h>

ENG_API Material::Material(const std::string& name)
	: Object(name), m_alpha{1.0f}, m_emission{glm::vec4(0.0f)}, m_ambient{glm::vec4(0.0f)}, m_specular{glm::vec4(0.0f)},
	m_diffuse{ glm::vec4(0.0f) }, m_shininess{ 1.0f }, m_texture{nullptr} {}

ENG_API void Material::setAlpha(const float& alpha) {
	if(alpha >= 0.0f && alpha <= 1.0f)
		this->m_alpha = alpha;
}

const ENG_API float& Material::getAlpha() const {
	return this->m_alpha;
}

ENG_API void Material::setEmission(const glm::vec3& emission) {
	this->m_emission = glm::vec4(emission, this->getAlpha());
}

const ENG_API glm::vec4& Material::getEmission() const {
	return this->m_emission;
}

ENG_API void Material::setAmbient(const glm::vec3& ambient) {
	this->m_ambient = glm::vec4(ambient, this->getAlpha());
}

const ENG_API glm::vec4& Material::getAmbient() const {
	return this->m_ambient;
}

ENG_API void Material::setSpecular(const glm::vec3& specular) {
	this->m_specular = glm::vec4(specular, this->getAlpha());
}

const ENG_API glm::vec4& Material::getSpecular() const {
	return this->m_specular;
}

ENG_API void Material::setDiffuse(const glm::vec3& diffuse) {
	this->m_diffuse = glm::vec4(diffuse, this->getAlpha());
}

const ENG_API glm::vec4& Material::getDiffuse() const {
	return this->m_diffuse;
}

ENG_API void Material::setShininess(const float& shininess) {
	if(shininess >= 0.0f)
		this->m_shininess = shininess;
}

const ENG_API float& Material::getShininess() const {
	return this->m_shininess;
}


ENG_API void Material::render(const glm::mat4& matrix) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(this->m_emission));
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, powf(2.0f, this->m_shininess));
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(this->m_ambient));
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(this->m_diffuse));
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(this->m_specular));
}

const ENG_API unsigned int Material::parse(const char* data, unsigned int& position) {
	char materialName[FILENAME_MAX];
	strncpy(materialName, data + position, sizeof(materialName) - 1);
	this->setName(materialName);
	position += (unsigned int)strlen(materialName) + 1;

	std::cout << "Parse: " << this->getName() << std::endl;


	// Material term colors, starting with emissive:
	glm::vec3 emission, albedo;
	memcpy(&emission, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	// Albedo:
	memcpy(&albedo, data + position, sizeof(glm::vec3));

	position += sizeof(glm::vec3);

	// Roughness factor:
	float roughness;
	memcpy(&roughness, data + position, sizeof(float));
	this->setShininess((1 - sqrt(roughness)) * 128);
	position += sizeof(float);

	// Metalness factor:
	float metalness;
	memcpy(&metalness, data + position, sizeof(float));
	position += sizeof(float);

	// Transparency factor:
	float alpha;
	memcpy(&alpha, data + position, sizeof(float));
	position += sizeof(float);

	// Albedo texture filename, or [none] if not used:
	char textureName[FILENAME_MAX];
	strncpy(textureName, data + position, sizeof(textureName) - 1);
	position += (unsigned int)strlen(textureName) + 1;

	this->setAlpha(alpha);
	this->setEmission(emission);
	this->setAmbient(albedo * 0.2f);
	this->setSpecular(albedo * 0.4f);
	this->setDiffuse(albedo * 0.6f);

	return 0;
}

