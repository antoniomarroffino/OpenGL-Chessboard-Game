#include "material.h"

ENG_API Material::Material(const std::string& name) : Object(name), m_texture{ nullptr } {}

ENG_API void Material::render(const glm::mat4& matrix) {

}

const ENG_API unsigned int Material::parse(const char* data, unsigned int& position) {
	char materialName[FILENAME_MAX];
	strcpy_s(materialName, data + position);
	this->setName(materialName);
	position += (unsigned int)strlen(materialName) + 1;


	//TODO: Da sistemare, aggiungere campi del materiale
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
	position += sizeof(float);

	// Metalness factor:
	float metalness;
	memcpy(&metalness, data + position, sizeof(float));
	position += sizeof(float);

	// Transparency factor:
	float alpha;
	memcpy(&alpha, data + position, sizeof(float));
	position += sizeof(float);

	return 0;
}

