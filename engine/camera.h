#pragma once

#include "node.h"

class Camera : public Node {
public:
	void virtual loadProjectionMatrix() const = 0;
	void virtual setProjectionMatrix() = 0;
	void reshapeWidthAndHeight(float, float);
	glm::mat4 getInverseCameraFinalMatrix() const;
protected:
	Camera(std::string, float, float, float, float);
	glm::mat4 m_projectionMatrix;
	float m_width;
	float m_height;
	float m_near;
	float m_far;
};