#include "camera.h"
#include "GL/freeglut.h"


ENG_API Camera::Camera(const std::string& name, const float& width, const float& height, const float& near_val, const float& far_val)
	: Node(name), m_projectionMatrix{ glm::mat4(1.0f) }, m_isCurrentCamera{ false }, m_width{ width }, m_height{ height }, m_near{ near_val }, m_far{ far_val } {}

void ENG_API Camera::reshapeWidthAndHeight(const float& width, const float& height) {
	this->m_width = width;
	this->m_height = height;
}

const ENG_API glm::mat4 Camera::getInverseCameraFinalMatrix() const {
	return glm::inverse(this->getFinalMatrix());
}

void ENG_API Camera::setMainCamera(const bool& val){
	this->m_isCurrentCamera = val;
}

const ENG_API bool& Camera::isMainCamera() const {
	return this->m_isCurrentCamera;
}

void ENG_API Camera::render(const glm::mat4& matrix) {
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(this->m_projectionMatrix));
	glMatrixMode(GL_MODELVIEW);
}