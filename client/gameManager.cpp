#include "gameManager.h"
#include <thread>
#include <chrono>
#include <filesystem>

struct GameManager::Reserved
{
	CameraManager& cameraManager;
	StatusManager statusManager;
	MovementManager& movementManager;
	Eng::Base& engine;
	Node* rootNode;
	std::array<std::array<Node*, 8>, 8> cheesboard;
	Node* rootResetNode;

	Reserved() : cameraManager{ CameraManager::getInstance() }, statusManager{ StatusManager() }, movementManager { MovementManager::getInstance() },
		engine{ Eng::Base::getInstance() }, rootNode{ nullptr }, cheesboard{ std::array<std::array<Node*, 8>, 8>() }, rootResetNode{ nullptr } {}
};

GameManager::GameManager() : m_reserved(std::make_unique<GameManager::Reserved>()) {}

GameManager::~GameManager() = default;

GameManager& GameManager::getInstance() {
	static GameManager instance;
	return instance;
}

void GameManager::keyboardCallbackPreGame(unsigned char key, int mouseX, int mouseY)
{
	Camera* mainCamera;
	switch (key)
	{
	case 32: // Change camera
		std::cout << "Space pressed" << std::endl;
		this->m_reserved->cameraManager.setNewMainCamera("playerWhiteCamera", this->m_reserved->rootNode);
		this->m_reserved->statusManager.changeState(GameStatus::GAME);
		break;
	}
}

void GameManager::specialKeyCallbackPreGame(int key, int mouseX, int mouseY)
{
	Camera* mainCamera;
	glm::mat4 currentMatrix, translationMatrix;
	switch (key) {
	case 100: // Left arrow
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		if (currentMatrix[3][2] > -21) {
			translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
			mainCamera->setMatrix(translationMatrix * currentMatrix);
		}
		break;
	case 101: // Up arrow
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		if (currentMatrix[3][1] < 24) {
			translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			mainCamera->setMatrix(translationMatrix * currentMatrix);
		}
		break;
	case 102: // Right arrow
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		if (currentMatrix[3][2] < 23) {
			translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			mainCamera->setMatrix(translationMatrix * currentMatrix);
		}
		break;
	case 103: // Dowm arrow
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		if (currentMatrix[3][1] > 6) {
			translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
			mainCamera->setMatrix(translationMatrix * currentMatrix);
		}
		break;
	}
}

std::list<std::string> GameManager::menuPreGame() {
	std::list<std::string> menu;
	menu.push_back("[Spacebar] Go to cheesboard view");
	menu.push_back("[Arrow key] Move camera");
	return menu;
}

void GameManager::keyboardCallbackGame(unsigned char key, int mouseX, int mouseY)
{
	Camera* mainCamera;
	switch (key)
	{
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;
		this->m_reserved->movementManager.changeTurn();
		if (this->m_reserved->movementManager.getTurn())
			this->m_reserved->cameraManager.setNewMainCamera("playerWhiteCamera", this->m_reserved->rootNode);
		else
			this->m_reserved->cameraManager.setNewMainCamera("playerBlackCamera", this->m_reserved->rootNode);
		break;
	case 27: // Exit from game
		std::cout << "Esc pressed" << std::endl;
		this->m_reserved->cameraManager.setNewMainCamera("firstCamera", this->m_reserved->rootNode);
		this->resetGame();
		this->renderScene();
		this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);
		break;
	case 32: // Change camera
		std::cout << "Space pressed" << std::endl;
		this->m_reserved->cameraManager.setNewMainCamera("firstCamera", this->m_reserved->rootNode);
		this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);
		break;
	case 127: // Delete
		std::cout << "Delete (Canc) pressed" << std::endl;
		
		break;
	case 'w':
	case 'W':
		std::cout << "w" << std::endl;
		this->m_reserved->movementManager.moveUp(this->m_reserved->cheesboard[0][1]);
		this->renderScene();
		break;
	case 'a':
	case 'A':
		std::cout << "a" << std::endl;
		this->m_reserved->movementManager.moveLeft(this->m_reserved->cheesboard[0][1]);
		this->renderScene();
		break;
	case 's':
	case 'S':
		std::cout << "s" << std::endl;
		this->m_reserved->movementManager.moveDown(this->m_reserved->cheesboard[0][1]);
		this->renderScene();
		break;
	case 'd':
	case 'D':
		std::cout << "d" << std::endl;
		this->m_reserved->movementManager.moveRight(this->m_reserved->cheesboard[0][1]);
		this->renderScene();
		break;
	case 'c':
	case 'C':
		std::cout << "c" << std::endl;
		break;
	}
}

void GameManager::specialKeyCallbackGame(int key, int mouseX, int mouseY)
{
	switch (key)
	{
	
	}
}

std::list<std::string> GameManager::menuGame() {
	std::list<std::string> menu;
	menu.push_back("[Spacebar] Go to scene view");
	menu.push_back("[Enter] Confirm choice/Switch mode");
	menu.push_back("[Canc] Delete choice/Switch mode");
	menu.push_back("[W - A - S - D] Move pawn");
	menu.push_back("Esc] Reset current game");
	return menu;
}

void GameManager::keyboardCallbackEndGame(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 32: // Change camera
		std::cout << "Space pressed" << std::endl;
		
		break;
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;

		break;
	}
}

void GameManager::specialKeyCallbackEndGame(int key, int mouseX, int mouseY)
{
	switch (key)
	{
	
	}
}

std::list<std::string> GameManager::menuEndGame() {
	std::list<std::string> menu;
	menu.push_back("[Spacebar] Go to ... view");
	return menu;
}

void GameManager::buildCheesboard() {
	this->m_reserved->cheesboard[0][0] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White rook"));
	this->m_reserved->cheesboard[0][1] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White knight.001"));
	this->m_reserved->cheesboard[0][2] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White bitshop.001"));
	this->m_reserved->cheesboard[0][3] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White queen"));
	this->m_reserved->cheesboard[0][4] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White king"));
	this->m_reserved->cheesboard[0][5] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White bitshop"));
	this->m_reserved->cheesboard[0][6] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White knight"));
	this->m_reserved->cheesboard[0][7] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White rook.001"));

	this->m_reserved->cheesboard[1][0] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("A"));
	this->m_reserved->cheesboard[1][1] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("B"));
	this->m_reserved->cheesboard[1][2] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("C"));
	this->m_reserved->cheesboard[1][3] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("D"));
	this->m_reserved->cheesboard[1][4] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("E"));
	this->m_reserved->cheesboard[1][5] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("F"));
	this->m_reserved->cheesboard[1][6] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("G"));
	this->m_reserved->cheesboard[1][7] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("H"));

	this->m_reserved->cheesboard[6][0] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("A.001"));
	this->m_reserved->cheesboard[6][1] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("B.001"));
	this->m_reserved->cheesboard[6][2] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("C.001"));
	this->m_reserved->cheesboard[6][3] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("D.001"));
	this->m_reserved->cheesboard[6][4] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("E.001"));
	this->m_reserved->cheesboard[6][5] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("F.001"));
	this->m_reserved->cheesboard[6][6] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("G.001"));
	this->m_reserved->cheesboard[6][7] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("H.001"));

	this->m_reserved->cheesboard[7][0] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black rook"));
	this->m_reserved->cheesboard[7][1] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black knight.001"));
	this->m_reserved->cheesboard[7][2] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black bitshop.001"));
	this->m_reserved->cheesboard[7][3] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black queen"));
	this->m_reserved->cheesboard[7][4] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black king"));
	this->m_reserved->cheesboard[7][5] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black bitshop"));
	this->m_reserved->cheesboard[7][6] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black knight"));
	this->m_reserved->cheesboard[7][7] = const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black rook.001"));
}

void GameManager::resetGame() {
	this->m_reserved->rootNode = this->m_reserved->rootResetNode->clone();
	this->buildCheesboard();
}

void GameManager::renderScene() {
	this->m_reserved->engine.clearScene();
	this->m_reserved->engine.passScene(this->m_reserved->rootNode);
}

void GameManager::startGame() {
	this->m_reserved->engine.init();

	this->m_reserved->statusManager.addGameStatusAndCallbacks(GameStatus::PRE_GAME,
		[](unsigned char key, int mouseX, int mouseY) { getInstance().keyboardCallbackPreGame(key, mouseX, mouseY); },
		[](int key, int mouseX, int mouseY) { getInstance().specialKeyCallbackPreGame(key, mouseX, mouseY); },
		this->menuPreGame());

	this->m_reserved->statusManager.addGameStatusAndCallbacks(GameStatus::GAME,
		[](unsigned char key, int mouseX, int mouseY) { getInstance().keyboardCallbackGame(key, mouseX, mouseY); },
		[](int key, int mouseX, int mouseY) { getInstance().specialKeyCallbackGame(key, mouseX, mouseY); },
		this->menuGame());

	this->m_reserved->statusManager.addGameStatusAndCallbacks(GameStatus::END_GAME,
		[](unsigned char key, int mouseX, int mouseY) { getInstance().keyboardCallbackEndGame(key, mouseX, mouseY); },
		[](int key, int mouseX, int mouseY) { getInstance().specialKeyCallbackEndGame(key, mouseX, mouseY); },
		this->menuEndGame());

	this->m_reserved->rootNode = this->m_reserved->engine.load("scene.ovo");
	if (this->m_reserved->rootNode == nullptr) {
		std::cerr << "ERROR: Error during parse of the scene" << std::endl;
		return;
	}

	this->createCameras();

	this->m_reserved->engine.passScene(this->m_reserved->rootNode);

	this->buildCheesboard();
	this->m_reserved->rootResetNode = this->m_reserved->rootNode->clone();

	this->gameLoop(); 
}


void GameManager::gameLoop() {
	this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);

	while (true) {
		this->m_reserved->engine.clear();

		this->m_reserved->engine.begin3D(this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode), 
				this->m_reserved->cameraManager.findCameraByName("menuCamera", this->m_reserved->rootNode), 
				this->m_reserved->statusManager.getMenu());

		//std::cout << "FPS: " << this->m_reserved->engine.getFPS() << std::endl;

		this->m_reserved->engine.swap();
		
		//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

void GameManager::createCameras() {
	Camera* startCamera = new PerspCamera("firstCamera", 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	startCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 12.0f, 15.0f))
	);
	this->m_reserved->cameraManager.addNewCamera(startCamera, this->m_reserved->rootNode);
	this->m_reserved->cameraManager.setNewMainCamera("firstCamera", this->m_reserved->rootNode);

	Camera* chessboardCamera = new PerspCamera("chessboardCamera", 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	chessboardCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 20.0f))
	);
	this->m_reserved->cameraManager.addNewCamera(chessboardCamera, this->m_reserved->rootNode);

	Camera* playerWhiteCamera = new PerspCamera("playerWhiteCamera", 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	playerWhiteCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 10.0f, 15.0f))
	);
	this->m_reserved->cameraManager.addNewCamera(playerWhiteCamera, this->m_reserved->rootNode);

	Camera* playerBlackCamera = new PerspCamera("playerBlackCamera", 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	playerBlackCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 10.0f, 15.0f))
	);
	this->m_reserved->cameraManager.addNewCamera(playerBlackCamera, this->m_reserved->rootNode);

	Camera* menuCamera = new OrthoCamera("menuCamera", 100.0f, 100.0f, -1.0f, 1.0f);
	this->m_reserved->cameraManager.addNewCamera(menuCamera, this->m_reserved->rootNode);
}