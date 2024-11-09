#pragma once

#include "camera.h"

class PerspCam : public Camera {
public:
	PerspCam(std::string name, float width, float height, float near, float far, float fovY);
	void loadProjectionMatrix() const override;
	void setProjectionMatrix() override;
private:
	float m_fovY;
};