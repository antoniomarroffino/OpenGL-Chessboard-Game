#include "orthoCamera.h"

ENG_API OrthoCamera::OrthoCamera(const std::string& name, const float& width, const float& height, const float& near, const float& far)
	:  Camera(name, width, height, near, far), m_left{0.0f}, m_bottom{0.0f}
{
	this->render();
}

void ENG_API OrthoCamera::loadProjectionMatrix() const {
	//gl load matrix con gl projection view per poi tornare a gl model view
}

void ENG_API OrthoCamera::render(const glm::mat4& matrix) {
	this->m_projectionMatrix = glm::ortho(this->m_left, this->m_width, this->m_bottom, this->m_height, this->m_near, this->m_far);
}