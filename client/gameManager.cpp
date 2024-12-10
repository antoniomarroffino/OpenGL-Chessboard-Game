#include "gameManager.h"
#include <windows.h>

struct GameManager::Reserved
{
	CameraManager& cameraManager;
	Eng::Base& engine;
	Node* rootNode;
	
	Reserved() : cameraManager{ CameraManager::getInstance() }, engine { Eng::Base::getInstance() }, rootNode{ nullptr }
	{}
};

GameManager::GameManager() : m_reserved(std::make_unique<GameManager::Reserved>()) {}

GameManager::~GameManager() = default;

GameManager& GameManager::getInstance()
{
	static GameManager instance;
	return instance;
}


void GameManager::startGame() {
	this->m_reserved->rootNode = this->m_reserved->engine.load("pippo.ovo");
	if (this->m_reserved->rootNode == nullptr) {
		std::cerr << "ERROR: Error during parse of the scene" << std::endl;
		return;
	}

	this->m_reserved->engine.init();

	this->createCameras();

	this->m_reserved->engine.passScene(this->m_reserved->rootNode);

	this->gameLoop(); 
}

void GameManager::gameLoop() {
	while (true) {
		this->m_reserved->engine.clear();

		this->m_reserved->engine.begin3D(this->m_reserved->cameraManager.getMainCamera(this->m_reserved->rootNode));

		std::cout << "FPS: " << this->m_reserved->engine.getFPS() << std::endl;

		this->m_reserved->engine.swap();

		//Sleep(3000);
	}
}

void GameManager::createCameras() {
	Camera* startCamera = new PerspCamera("firstCamera", 100.0f, 100.0f, 1.0f, 1000.0f, glm::radians(45.0f));
	startCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 7.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 20.0f))
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
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 7.0f))
	);


	this->m_reserved->cameraManager.addNewCamera(chessboardCamera, this->m_reserved->rootNode);
	//this->m_reserved->cameraManager.setNewMainCamera("chessboardCamera", this->m_reserved->rootNode);
}