#include "gameManager.h"
#include <thread>
#include <chrono>
#include <filesystem>

struct GameManager::Reserved
{
	CameraManager& cameraManager;
	StatusManager statusManager;
	Eng::Base& engine;
	Node* rootNode;
	
	Reserved() : cameraManager{ CameraManager::getInstance() }, statusManager{ StatusManager() }, engine{Eng::Base::getInstance()}, rootNode{nullptr}
	{}
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
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;

		break;
	case 32: // Change camera
		std::cout << "Space pressed" << std::endl;
		mainCamera = dynamic_cast<Camera*>(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("chessboardCamera")));
		this->m_reserved->cameraManager.setNewMainCamera(mainCamera->getName(), this->m_reserved->rootNode);
		this->m_reserved->statusManager.changeState(GameStatus::GAME);
		break;
	case 127: // Delete choice
		std::cout << "Delete pressed" << std::endl;
		break;
	}
}

void GameManager::specialKeyCallbackPreGame(int key, int mouseX, int mouseY)
{
	Camera* mainCamera;
	glm::mat4 currentMatrix, translationMatrix;
	switch (key) {
	case 100: // Left arrow
		std::cout << "Left arrow pressed" << std::endl;
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
		mainCamera->setMatrix(translationMatrix * currentMatrix);
		break;
	case 101: // Up arrow
		std::cout << "Up arrow pressed" << std::endl;
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 10.0f, 0.0f));
		mainCamera->setMatrix(translationMatrix * currentMatrix);
		break;
	case 102: // Right arrow
		std::cout << "Right arrow pressed" << std::endl;
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 10.0f));
		mainCamera->setMatrix(translationMatrix * currentMatrix);
		break;
	case 103: // Dowm arrow
		std::cout << "Down arrow pressed" << std::endl;
		mainCamera = this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode);
		currentMatrix = mainCamera->getMatrix();
		translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f));
		mainCamera->setMatrix(translationMatrix * currentMatrix);
		break;
	}
}

std::list<std::string> GameManager::menuPreGame() {
	std::list<std::string> menu;
	menu.push_back("ANTO GAY");
	return menu;
}

void GameManager::keyboardCallbackGame(unsigned char key, int mouseX, int mouseY)
{
	Camera* mainCamera;
	switch (key)
	{
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;

		break;
	case 32: // Change camera
		std::cout << "Space pressed" << std::endl;
		mainCamera = dynamic_cast<Camera*>(const_cast<Node*>(this->m_reserved->rootNode->findNodeByName("firstCamera")));
		this->m_reserved->cameraManager.setNewMainCamera(mainCamera->getName(), this->m_reserved->rootNode);
		this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);
		break;
	case 'w':
	case 'W':
		std::cout << "w" << std::endl;
		break;
	case 'a':
	case 'A':
		std::cout << "a" << std::endl;
		break;
	case 's':
	case 'S':
		std::cout << "s" << std::endl;
		break;
	case 'd':
	case 'D':
		std::cout << "d" << std::endl;
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
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;

		break;
	}
}

std::list<std::string> GameManager::menuGame() {
	std::list<std::string> menu;
	menu.push_back("ADEL GAY");
	return menu;
}

void GameManager::keyboardCallbackEndGame(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;

		break;
	}
}

void GameManager::specialKeyCallbackEndGame(int key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 13: // Confirm choice
		std::cout << "Enter pressed" << std::endl;

		break;
	}
}

std::list<std::string> GameManager::menuEndGame() {
	std::list<std::string> menu;
	//menu.push_back("ANTO GAY");
	return menu;
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

	this->gameLoop(); 
}


void GameManager::gameLoop() {
	this->m_reserved->statusManager.changeState(GameStatus::PRE_GAME);

	while (true) {
		this->m_reserved->engine.clear();

		this->m_reserved->engine.begin3D(this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode), 
				this->m_reserved->cameraManager.findCameraByName("menuCamera", this->m_reserved->rootNode), this->m_reserved->statusManager.getMenu());

		std::cout << "FPS: " << this->m_reserved->engine.getFPS() << std::endl;

		this->m_reserved->engine.swap();
		
		//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}

void GameManager::createCameras() {
	Camera* startCamera = new PerspCamera("firstCamera", 100.0f, 100.0f, 1.0f, 1000.0f, glm::radians(45.0f));
	startCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 12.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 15.0f))
	);
	this->m_reserved->cameraManager.addNewCamera(startCamera, this->m_reserved->rootNode);
	this->m_reserved->cameraManager.setNewMainCamera("firstCamera", this->m_reserved->rootNode);

	Camera* chessboardCamera = new PerspCamera("chessboardCamera", 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	chessboardCamera->setMatrix(
		glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))
	);
	chessboardCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(2.1f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.6f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 20.0f))
	);
	this->m_reserved->cameraManager.addNewCamera(chessboardCamera, this->m_reserved->rootNode);

	Camera* menuCamera = new OrthoCamera("menuCamera", 100.0f, 100.0f, -1.0f, 1.0f);
	this->m_reserved->cameraManager.addNewCamera(menuCamera, this->m_reserved->rootNode);
}