#include "camera.h"

Camera::Camera(std::string name, float width, float height, float near, float far)
	: Node(name), m_width{width}, m_height{height}, m_near{near}, m_far{far} {}

void Camera::reshapeWidthAndHeight(float width, float height) {
	m_width = width;
	m_height = height;
}

glm::mat4 Camera::getInverseCameraFinalMatrix() const {
	return glm::inverse(this->getFinalMatrix());
}