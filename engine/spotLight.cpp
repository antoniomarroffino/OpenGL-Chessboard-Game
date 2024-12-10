#include "spotLight.h"

#include <GL/freeglut.h>


ENG_API SpotLight::SpotLight(const std::string& name, const glm::vec3& position, const glm::vec3& direction, const float& cutoff) 
    : Light(name, glm::vec4(position, 1.0f)), m_direction{ direction }, m_cutoff{ cutoff } 
{
    if (cutoff < 0.0f || cutoff > 90.0f)
        this->m_cutoff = 45.0f;
}

ENG_API void SpotLight::setDirection(const glm::vec3& direction) {
    this->m_direction = direction;
}

const ENG_API glm::vec3& SpotLight::getDirection() const {
    return m_direction;
}

ENG_API void SpotLight::setCutoff(const float& cutoff) {
    if (cutoff >= 0.0f && cutoff <= 90.0f)
        this->m_cutoff = cutoff;
}

const ENG_API float& SpotLight::getCutoff() const {
    return this->m_cutoff;
}

void ENG_API SpotLight::render(const glm::mat4& matrix) {
    Light::render(matrix);
    glLightfv(Light::lightActiveCounter, GL_SPOT_CUTOFF, &this->getCutoff());
    glLightfv(Light::lightActiveCounter, GL_SPOT_DIRECTION, glm::value_ptr(this->getDirection()));
    Light::lightActiveCounter++;
}

const ENG_API unsigned int SpotLight::parse(const char* data, unsigned int& position) {
	const unsigned int& children = Light::parse(data, position);

    // Direction:
    glm::vec3 direction;
    memcpy(&direction, data + position, sizeof(glm::vec3));
    position += sizeof(glm::vec3);
    this->setDirection(direction);

    //cutoff
    float cutoff;
    memcpy(&cutoff, data + position, sizeof(float));
    position += sizeof(float);
    this->setCutoff(cutoff);

	return children;
}