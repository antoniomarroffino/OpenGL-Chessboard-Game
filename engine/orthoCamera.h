/**
 * @file		orthoCamera.h
 * @brief	OrthoCamera include file
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
 // MAIN ORTHOCAMERA CLASS //
 ///////////////////////

 /**
  * @brief Concrete OrthoCamera class
  */
class ENG_API OrthoCamera : public Camera {
public:
	OrthoCamera(const std::string& name, const float& width, const float& height, const float& near_val, const float& far_val);
	OrthoCamera(const OrthoCamera&);
	OrthoCamera& operator=(const OrthoCamera&) = delete;

	Node* clone() const override;
	void loadProjectionMatrix() override;
private:
	float m_left;
	float m_bottom;
};
