/**
 * @file		camera.h
 * @brief	Camera include file
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
#include "node.h"
#include "glm/gtc/matrix_transform.hpp"


 ///////////////////////
 // MAIN CAMERA CLASS //
 ///////////////////////

 /**
  * @brief Abstract base Camera class
  */
class ENG_API Camera : public Node {
public:
	void virtual loadProjectionMatrix() const = 0;
	void virtual render(const glm::mat4& = glm::mat4(1.0f)) override = 0;

	void reshapeWidthAndHeight(const float&, const float&);
	const glm::mat4 getInverseCameraFinalMatrix() const;
	void setMainCamera(const bool&);
	virtual const bool& isMainCamera() const;
protected:
	Camera(const std::string&, const float&, const float&, const float&, const float&);
	virtual ~Camera() = default;

	glm::mat4 m_projectionMatrix;
	bool m_isCurrentCamera;
	float m_width;
	float m_height;
	float m_near;
	float m_far;
};