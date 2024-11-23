#include "camera.h"

ENG_API Camera::Camera(const std::string& name, const float& width, const float& height, const float& near, const float& far)
	: Node(name), m_projectionMatrix{ glm::mat4(1.0f) }, m_isCurrentCamera{ false }, m_width{ width }, m_height{ height }, m_near{ near }, m_far{ far } {}

ENG_API void Camera::reshapeWidthAndHeight(const float& width, const float& height) {
	this->m_width = width;
	this->m_height = height;
}

const ENG_API glm::mat4 Camera::getInverseCameraFinalMatrix() const {
	return glm::inverse(this->getFinalMatrix());
}

ENG_API void Camera::setMainCamera(const bool& val){
	this->m_isCurrentCamera = val;
}

const ENG_API bool& Camera::isMainCamera() {
	return this->m_isCurrentCamera;
}

const ENG_API Node* Camera::getCamera() const {
	if (this->m_isCurrentCamera)
		return this;
	return nullptr;
}