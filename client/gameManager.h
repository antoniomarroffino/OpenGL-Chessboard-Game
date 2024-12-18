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

	void keyboardCallbackPreGame(unsigned char, int, int);
	void specialKeyCallbackPreGame(int, int, int);

	void keyboardCallbackGame(unsigned char, int, int);
	void specialKeyCallbackGame(int, int, int);

	void keyboardCallbackEndGame(unsigned char, int, int);
	void specialKeyCallbackEndGame(int, int, int);

	GameManager();
	
	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
};