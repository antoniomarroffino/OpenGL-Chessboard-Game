#pragma once

#include <memory>
#include "statusManager.h"
#include "cameraManager.h"
#include "movementManager.h"
#include "listOfPiecesManager.h"
#include <array>
#include "engine.h"
#include "node.h"
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
	void initialize();

	void gameLoop();
	void buildChessboard();
	void resetGame();
	void renderScene();

	void keyboardCallbackPreGame(unsigned char, int, int);
	void specialKeyCallbackPreGame(int, int, int);
	std::list<std::string> menuPreGame();

	void keyboardCallbackGame(unsigned char, int, int);
	void specialKeyCallbackGame(int, int, int);
	std::list<std::string> menuGame();

	void keyboardCallbackEndGame(unsigned char, int, int);
	void specialKeyCallbackEndGame(int, int, int);
	std::list<std::string> menuEndGame();

	GameManager();
	
	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
};