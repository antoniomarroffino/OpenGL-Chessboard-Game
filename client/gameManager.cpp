#include "gameManager.h"
#include <thread>
#include <chrono>
#include <filesystem>

struct GameManager::Reserved
{
	CameraManager& cameraManager;
	StatusManager& statusManager;
	MovementManager& movementManager;
	ListOfPiecesManager& listOfPiecesManager;
	Eng::Base& engine;
	Node* rootNode;
	Node* rootResetNode;
	bool isChoiceMode;	// TRUE -> move SelectPointer - FALSE -> move Piece

	Reserved() : cameraManager{ CameraManager::getInstance() }, 
		statusManager{ StatusManager::getInstance() }, 
		movementManager{MovementManager::getInstance()},
		listOfPiecesManager{ListOfPiecesManager::getInstance()},
		engine{ Eng::Base::getInstance() }, 
		rootNode{ nullptr },
		rootResetNode{ nullptr }, 
		isChoiceMode{ false } {
	}
};

GameManager::GameManager() : m_reserved(std::make_unique<GameManager::Reserved>()) { this->initialize(); }

GameManager::~GameManager() {
	this->m_reserved->engine.free();
}

GameManager& GameManager::getInstance() {
	static GameManager instance;
	return instance;
}

void GameManager::keyboardCallbackPreGame(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 32: // Change camera
		this->m_reserved->isChoiceMode = true;
		this->m_reserved->statusManager.changeState(GameStatus::GAME);
		break;
	}
	this->renderScene();
}

void GameManager::specialKeyCallbackPreGame(int key, int mouseX, int mouseY)
{
	switch (key) {
	case 100: // Left arrow
		this->m_reserved->cameraManager.moveCameraLeft();
		break;
	case 101: // Up arrow
		this->m_reserved->cameraManager.moveCameraUp();
		break;
	case 102: // Right arrow
		this->m_reserved->cameraManager.moveCameraRight();
		break;
	case 103: // Dowm arrow
		this->m_reserved->cameraManager.moveCameraDown();
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
	switch (key)
	{
	case 13: // Confirm choice
		if (this->m_reserved->isChoiceMode) {
			this->m_reserved->listOfPiecesManager.confirmChoice();
		}
		else {
			bool isMovedCorrectly = this->m_reserved->listOfPiecesManager.confirmMove();
			if (!isMovedCorrectly) break;
			this->m_reserved->movementManager.changeTurn();
			if (this->m_reserved->movementManager.getTurn())
				this->m_reserved->cameraManager.setNewMainCamera(PLAYER_WHITE_CAMERA);
			else
				this->m_reserved->cameraManager.setNewMainCamera(PLAYER_BLACK_CAMERA);
		}
		this->m_reserved->isChoiceMode = !this->m_reserved->isChoiceMode;
		break;
	case 27: // Exit from game
		this->resetGame();
		this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);
		break;
	case 127:
		if (!this->m_reserved->isChoiceMode) {
			this->m_reserved->listOfPiecesManager.deleteChoice();
			this->m_reserved->isChoiceMode = true;
		}
		break;
	}

	//PIECE MOVEMENT
	if (!this->m_reserved->isChoiceMode) {
		switch (key) {
		case 'w':
		case 'W':
			this->m_reserved->movementManager.moveUp(this->m_reserved->listOfPiecesManager.getChoosenPiece());
			break;
		case 'a':
		case 'A':
			this->m_reserved->movementManager.moveLeft(this->m_reserved->listOfPiecesManager.getChoosenPiece());
			break;
		case 's':
		case 'S':
			this->m_reserved->movementManager.moveDown(this->m_reserved->listOfPiecesManager.getChoosenPiece());
			break;
		case 'd':
		case 'D':
			this->m_reserved->movementManager.moveRight(this->m_reserved->listOfPiecesManager.getChoosenPiece());
			break;
		}
	}

	this->renderScene();
}

void GameManager::specialKeyCallbackGame(int key, int mouseX, int mouseY)
{
	if (!this->m_reserved->isChoiceMode) return;

	switch (key) {
	case 100: // Left arrow
		this->m_reserved->listOfPiecesManager.moveChooseNodeLeft();
		break;
	case 102: // Right arrow
		this->m_reserved->listOfPiecesManager.moveChooseNodeRight();
		break;
	}

	this->renderScene();
}

std::list<std::string> GameManager::menuGame() {
	std::list<std::string> menu;
	menu.push_back("[Enter] Confirm choice/Switch mode");
	menu.push_back("[CANC] Return to initial position");
	menu.push_back("[Arrow key] Move camera");
	menu.push_back("[W - A - S - D] Move piece");
	menu.push_back("[Esc] Reset current game");
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
	/*switch (key)
	{
	
	}*/
}

std::list<std::string> GameManager::menuEndGame() {
	std::list<std::string> menu;
	menu.push_back("[Spacebar] Go to ... view");
	return menu;
}

void GameManager::buildChessboard() {
	this->m_reserved->listOfPiecesManager.clearLists();

	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;

	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White rook")), 0, 0));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White knight.001")), 0, 1));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White bitshop.001")), 0, 2));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White queen")), 0, 3));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White king")), 0, 4));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White bitshop")), 0, 5));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White knight")), 0, 6));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("White rook.001")), 0, 7));

	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("A")), 1, 0));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("B")), 1, 1));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("C")), 1, 2));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("D")), 1, 3));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("E")), 1, 4));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("F")), 1, 5));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("G")), 1, 6));
	whitePieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("H")), 1, 7));

	ListOfPieces* white = new ListOfPieces(whitePieces);

	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black rook.001")), 7, 7));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black knight")), 7, 6));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black bitshop")), 7, 5));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black king")), 7, 4));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black queen")), 7, 3));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black bitshop.001")), 7, 2));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black knight.001")), 7, 1));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("Black rook")), 7, 0));

	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("H.001")), 6, 7));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("G.001")), 6, 6));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("F.001")), 6, 5));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("E.001")), 6, 4));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("D.001")), 6, 3));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("C.001")), 6, 2));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("B.001")), 6, 1));
	blackPieces.push_back(new Piece(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("A.001")), 6, 0));

	ListOfPieces* black = new ListOfPieces(blackPieces);

	this->m_reserved->listOfPiecesManager.initialize(white, black, this->m_reserved->rootNode);
}

void GameManager::resetGame() {
	this->m_reserved->rootNode = this->m_reserved->rootResetNode->clone();
	this->buildChessboard();
}

void GameManager::renderScene() {
	this->m_reserved->engine.clearScene();
	this->m_reserved->engine.passScene(this->m_reserved->rootNode);
}

void GameManager::startGame() {
	this->m_reserved->rootNode = this->m_reserved->engine.load("scenaDef.ovo");
	if (this->m_reserved->rootNode == nullptr) {
		std::cerr << "ERROR: Error during parse of the scene" << std::endl;
		return;
	}

	this->m_reserved->cameraManager.initialize(this->m_reserved->rootNode);

	this->buildChessboard();

	this->m_reserved->rootResetNode = this->m_reserved->rootNode->clone();

	this->m_reserved->engine.passScene(this->m_reserved->rootNode);

	this->gameLoop(); 
}


void GameManager::gameLoop() {
	this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);

	while (true) {
		this->m_reserved->engine.clear();

		this->m_reserved->engine.begin3D(this->m_reserved->cameraManager.getMainCamera(), 
				this->m_reserved->cameraManager.findCameraByName(MENU_CAMERA), 
				this->m_reserved->statusManager.getMenu());

		std::cout << "FPS: " << this->m_reserved->engine.getFPS() << std::endl;

		this->m_reserved->engine.swap();
		
		// std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

void GameManager::initialize() {
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
}