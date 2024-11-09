#include "perspCam.h"

PerspCam::PerspCam(std::string name, float width, float height, float near, float far, float fovY)
	: Camera(name, width, height, near, far), m_fovY{ fovY } 
{
	this->setProjectionMatrix();
}

void PerspCam::loadProjectionMatrix() const {
	//gl load matrix con gl projection view per poi tornare a gl model view
}

void PerspCam::setProjectionMatrix() {
	this->m_projectionMatrix = glm::perspective(m_fovY, m_width / m_height, m_near, m_far);
}