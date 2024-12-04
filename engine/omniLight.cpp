#include "omniLight.h"

ENG_API OmniLight::OmniLight(const std::string& name, const glm::vec3& position) : Light(name, glm::vec4(position, 1.0f)), m_cutoff{ 180.0f } {}

const ENG_API float& OmniLight::getCutoff() const {
	return this->m_cutoff;
}

void ENG_API OmniLight::render(const glm::mat4& matrix) {

}

const unsigned int OmniLight::parse(const char* data, unsigned int& position) {
	const unsigned int& children = Light::parse(data, position);

	return children;
}