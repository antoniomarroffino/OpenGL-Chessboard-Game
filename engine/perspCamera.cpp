#include "perspCamera.h"

PerspCamera::PerspCamera(const std::string& name, const float& width, const float& height, const float& near, const float& far, const float& fovY)
	: Camera(name, width, height, near, far), m_fovY{ fovY } 
{
	this->render();
}

void PerspCamera::loadProjectionMatrix() const {
	//gl load matrix con gl projection view per poi tornare a gl model view
}

void PerspCamera::render(const glm::mat4& matrix) {
	this->m_projectionMatrix = glm::perspective(m_fovY, m_width / m_height, m_near, m_far);
}