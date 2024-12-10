#include "light.h"
#include <GL/freeglut.h>


unsigned int Light::lightActiveCounter{ GL_LIGHT0 };
unsigned int Light::maxNumberOfActiveLights{ GL_LIGHT0 + 7 };

ENG_API Light::Light(const std::string& name, const glm::vec4& position) : Node(name), m_position{ position }, m_lightMaterial{ nullptr } {}

ENG_API void Light::setPosition(const glm::vec3& position) {
	this->m_position = glm::vec4(position, 1.0f);
}

const ENG_API glm::vec4& Light::getPosition() const {
	return this->m_position;
}

ENG_API void Light::resetLightCounter() {
	for (unsigned int lightCounter = GL_LIGHT0; lightCounter < Light::lightActiveCounter; lightCounter++) glDisable(lightCounter);
	Light::lightActiveCounter = GL_LIGHT0;
}

ENG_API void Light::render(const glm::mat4& matrix) {
	if (this->m_lightMaterial == nullptr) return;
	if (Light::lightActiveCounter > Light::maxNumberOfActiveLights) return;

	glEnable(Light::lightActiveCounter);
	glMatrixMode(GL_MODELVIEW);
	glLightfv(Light::lightActiveCounter, GL_AMBIENT, glm::value_ptr(this->m_lightMaterial->getAmbient()));
	glLightfv(Light::lightActiveCounter, GL_DIFFUSE, glm::value_ptr(this->m_lightMaterial->getDiffuse()));
	glLightfv(Light::lightActiveCounter, GL_SPECULAR, glm::value_ptr(this->m_lightMaterial->getSpecular()));
	glm::vec4 transformedPosition = matrix * glm::vec4(this->getPosition());
	glLightfv(Light::lightActiveCounter, GL_POSITION, glm::value_ptr(transformedPosition));
}

const ENG_API unsigned int Light::parse(const char* data, unsigned int& position) {
	unsigned int children = Node::parse(data, position);

	//subtype
	position += sizeof(unsigned char);

	// Light color:
	glm::vec3 color;
	memcpy(&color, data + position, sizeof(glm::vec3));
	position += sizeof(glm::vec3);

	this->m_lightMaterial = new Material();
	this->m_lightMaterial->setAmbient(color);
	this->m_lightMaterial->setDiffuse(color);
	this->m_lightMaterial->setSpecular(color);

	//Radius
	position += sizeof(float);


	return children;
}
