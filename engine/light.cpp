#include "light.h"

ENG_API Light::Light(const std::string& name, const glm::vec4& position) : Node(name), m_position{ position } {}

ENG_API void Light::setPosition(const glm::vec3& position) {
	this->m_position = glm::vec4(position, 1.0f);
}

const ENG_API glm::vec4& Light::getPosition() const {
	return this->m_position;
}

const ENG_API unsigned int Light::parse(const char* data, unsigned int& position) {
	unsigned int children = Node::parse(data, position);

	//subtype
	position += sizeof(unsigned char);

	// Light color:
	glm::vec3 color;
	memcpy(&color, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	//Radius
	position += sizeof(float);


	return children;
}
