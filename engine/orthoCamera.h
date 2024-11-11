#pragma once

#include "camera.h"

class OrthoCamera : public Camera {
public:
	OrthoCamera(const std::string& name, const float& width, const float& height, const float& near, const float& far);
	void loadProjectionMatrix() const override;
	void render(const glm::mat4& = glm::mat4(1.0f)) override;
private:
	float m_left;
	float m_bottom;
};
