#include "perspCamera.h"

PerspCamera::PerspCamera(const std::string& name, const float& width, const float& height, const float& near_val, const float& far_val, const float& fovY)
	: Camera(name, width, height, near_val, far_val), m_fovY{ fovY }
{
	this->loadProjectionMatrix();
}

void PerspCamera::loadProjectionMatrix() {
	//gl load matrix con gl projection view per poi tornare a gl model view
	this->m_projectionMatrix = glm::perspective(m_fovY, m_width / m_height, m_near, m_far);
}