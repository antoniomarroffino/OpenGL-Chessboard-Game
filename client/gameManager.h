#pragma once

#include <memory>
#include "cameraManager.h"
#include "engine.h"
#include "node.h"
#include "perspCamera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class GameManager {
public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	~GameManager();

	static GameManager& getInstance();
	void startGame();
private:
	void gameLoop();
	void createCameras();

	GameManager();
	
	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
};