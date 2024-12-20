#pragma once

#include "node.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MovementManager
{
public:
	MovementManager(const MovementManager&) = delete;
	MovementManager& operator=(const MovementManager&) = delete;
	~MovementManager();

	static MovementManager& getInstance();

	void moveRight(Node* node);
	void moveLeft(Node* node);
	void moveUp(Node* node);
	void moveDown(Node* node);

private:
	MovementManager();
	float getFactoryByTurn() const;

	// True: white - False: black
	bool m_turn;
	const float MOVEMENT_SPACE = 0.54f;
};