#pragma once

#include "camera.h"

class OrthoCamera : public Camera {
public:
	OrthoCamera(std::string name, float width, float height, float near, float far);
	void loadProjectionMatrix() const override;
	void setProjectionMatrix() override;
private:
	float m_left;
	float m_bottom;
};
