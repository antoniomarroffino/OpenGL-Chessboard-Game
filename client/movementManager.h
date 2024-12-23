#pragma once

#include <array>
#include "onStateUpdate.h"
#include "statusManager.h"
#include "piece.h"
#include "node.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class MovementManager : public OnStateUpdateListener
{
public:
	MovementManager(const MovementManager&) = delete;
	MovementManager& operator=(const MovementManager&) = delete;
	~MovementManager();

	static MovementManager& getInstance();

	bool getTurn() const;
	float getFactoryByTurn() const;

	void changeTurn();
	void moveRight(Piece*);
	void moveLeft(Piece*);
	void moveUp(Piece*);
	void moveDown(Piece*);

private:
	MovementManager();

	void preGameHandler() override;

	bool m_turn;  // TRUE -> white - FALSE -> black
	StatusManager& m_statusManager;
	const float MOVEMENT_SPACE = 0.54f;
};