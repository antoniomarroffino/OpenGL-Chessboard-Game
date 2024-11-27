/**
 * @file		perspCamera.h
 * @brief	 PerspCamera include file
 *
 * @author	Luca Fantò (C) SUPSI [luca.fanto@student.supsi.ch]
 * @author	Mattia Cainarca (C) SUPSI [mattia.cainarca@student.supsi.ch]
 * @author	Antonio Marroffino (C) SUPSI [antonio.marroffino@student.supsi.ch]
 */
#pragma once


 //////////////
 // #INCLUDE //
 //////////////

	// C/C++:
#include "camera.h"


 ///////////////////////
 // MAIN PERSPCAMERA CLASS //
 ///////////////////////

 /**
  * @brief Concrete PerspCamera class
  */
class ENG_API PerspCamera : public Camera {
public:
	PerspCamera(const std::string& name, const float& width, const float& height, const float& near, const float& far, const float& fovY);
	void loadProjectionMatrix() const override;
	void render(const glm::mat4& = glm::mat4(1.0f)) override;
private:
	float m_fovY;
};