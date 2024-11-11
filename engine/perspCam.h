#pragma once

#include "camera.h"

class PerspCam : public Camera {
public:
	PerspCam(const std::string& name, const float& width, const float& height, const float& near, const float& far, const float& fovY);
	void loadProjectionMatrix() const override;
	void render(const glm::mat4& = glm::mat4(1.0f)) override;
private:
	float m_fovY;
};