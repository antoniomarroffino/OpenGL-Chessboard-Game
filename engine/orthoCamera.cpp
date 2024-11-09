#include "orthoCamera.h"

OrthoCamera::OrthoCamera(std::string name, float width, float height, float near, float far)
	:  Camera(name, width, height, near, far), m_left{0.0f}, m_bottom{0.0f}
{
	this->setProjectionMatrix();
}

void OrthoCamera::loadProjectionMatrix() const {
	//gl load matrix con gl projection view per poi tornare a gl model view
}

void OrthoCamera::setProjectionMatrix() {
	this->m_projectionMatrix = glm::ortho(this->m_left, this->m_width, this->m_bottom, this->m_height, this->m_near, this->m_far);
}