#include "omniLight.h"
#include <GL/freeglut.h>

ENG_API OmniLight::OmniLight(const std::string& name, const glm::vec3& position) : Light(name, glm::vec4(position, 1.0f)), m_cutoff{ 180.0f } {}

const ENG_API float& OmniLight::getCutoff() const {
	return this->m_cutoff;
}

void ENG_API OmniLight::render(const glm::mat4& matrix) {
    std::cout << "render omnilight" << std::endl;
    Light::render(matrix);
    glLightfv(Light::lightActiveCounter, GL_SPOT_CUTOFF, &this->m_cutoff);

    Light::lightActiveCounter++;
} 