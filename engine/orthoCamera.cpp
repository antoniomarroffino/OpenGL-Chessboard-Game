#include "orthoCamera.h"

ENG_API OrthoCamera::OrthoCamera(const std::string& name, const float& width, const float& height, const float& near_val, const float& far_val)
	:  Camera(name, width, height, near_val, far_val), m_left{0.0f}, m_bottom{0.0f}
{
	this->loadProjectionMatrix();
}

void ENG_API OrthoCamera::loadProjectionMatrix() {
	this->m_projectionMatrix = glm::ortho(this->m_left, this->m_width, this->m_bottom, this->m_height);
	//gl load matrix con gl projection view per poi tornare a gl model view
}