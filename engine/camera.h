#pragma once

#include "node.h"

class Camera : public Node {
public:
	void virtual loadProjectionMatrix() const = 0;
	void virtual render(const glm::mat4& = glm::mat4(1.0f)) override = 0;
	const Node* getCamera() const override;

	void reshapeWidthAndHeight(const float&, const float&);
	const glm::mat4 getInverseCameraFinalMatrix() const;
	void setMainCamera(const bool&);
	const bool& isMainCamera();
protected:
	Camera(const std::string&, const float&, const float&, const float&, const float&);
	glm::mat4 m_projectionMatrix;
	bool m_isCurrentCamera;
	float m_width;
	float m_height;
	float m_near;
	float m_far;
};