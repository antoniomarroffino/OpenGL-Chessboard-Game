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
	PerspCamera(const std::string& name, const float& width, const float& height, const float& near_val, const float& far_val, const float& fovY);
	PerspCamera(const PerspCamera&);
	PerspCamera& operator=(const PerspCamera&) = delete;

	Node* clone() const override;
	void loadProjectionMatrix() override;
private:
	float m_fovY;
};