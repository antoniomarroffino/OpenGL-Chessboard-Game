#include "cameraManager.h"

CameraManager::CameraManager() : OnStateUpdateListener(), m_rootNode{nullptr}, m_statusManager{StatusManager::getInstance()}
{
	this->m_statusManager.subscribeListener(GameStatus::PRE_GAME, this);
	this->m_statusManager.subscribeListener(GameStatus::GAME, this);
}

CameraManager& CameraManager::getInstance() {
	static CameraManager instance;
	return instance;
}

bool CameraManager::initialize(Node* rootNode) {
	if (rootNode == nullptr) return false;

	this->m_rootNode = rootNode;
	this->createCameras();

	return true;
}

void CameraManager::createCameras() {
	Camera* startCamera = new PerspCamera(MAIN_CAMERA, 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	startCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 12.0f, 15.0f))
	);
	this->addNewCamera(startCamera);

	Camera* chessboardCamera = new PerspCamera(CHESSBOARD_CAMERA, 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	chessboardCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 20.0f))
	);
	this->addNewCamera(chessboardCamera);

	Camera* playerWhiteCamera = new PerspCamera(PLAYER_WHITE_CAMERA, 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	playerWhiteCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 10.0f, 15.0f))
	);
	this->addNewCamera(playerWhiteCamera);

	Camera* playerBlackCamera = new PerspCamera(PLAYER_BLACK_CAMERA, 100.0f, 100.0f, 1.0f, 100.0f, glm::radians(45.0f));
	playerBlackCamera->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 10.0f, 15.0f))
	);
	this->addNewCamera(playerBlackCamera);

	Camera* menuCamera = new OrthoCamera(MENU_CAMERA, 100.0f, 100.0f, -1.0f, 1.0f);
	this->addNewCamera(menuCamera);
}

bool CameraManager::addNewCamera(Camera* newCamera, Node* parentNode) {
	if (newCamera == nullptr) return false;

	if (parentNode == nullptr) parentNode = this->m_rootNode;

	return parentNode->addChild(newCamera);
}

bool CameraManager::removeCamera(const std::string& cameraName, Node* parentNode) {
	if (parentNode == nullptr) parentNode = this->m_rootNode;

	return parentNode->removeChild(const_cast<Node*>(parentNode->findNodeByName(cameraName)));
}

bool CameraManager::setNewMainCamera(const std::string& cameraName, Node* parentNode) const {
	if (parentNode == nullptr) parentNode = this->m_rootNode;

	Camera* oldMainCamera = dynamic_cast<Camera*>(parentNode->getMainCamera());
	
	if (oldMainCamera != nullptr) oldMainCamera->setMainCamera(false);

	Camera* newMainCamera = dynamic_cast<Camera*>(const_cast<Node*>(parentNode->findNodeByName(cameraName)));

	if (newMainCamera == nullptr) return false;

	newMainCamera->setMainCamera(true);
	return true;
}

Camera* CameraManager::getMainCamera(const Node* parentNode) const {
	if (parentNode == nullptr) parentNode = this->m_rootNode;

	return dynamic_cast<Camera*>((parentNode->getMainCamera()));
}

Camera* CameraManager::findCameraByName(const std::string& cameraName, const Node* parentNode) const {
	if (parentNode == nullptr) parentNode = this->m_rootNode;

	return dynamic_cast<Camera*>(const_cast<Node*>(parentNode->findNodeByName(cameraName)));
}

void CameraManager::moveCameraRight() {
	Camera* mainCamera = this->findCameraByName(MAIN_CAMERA);

	if (mainCamera->getMatrix()[3][2] < 23) mainCamera->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * mainCamera->getMatrix());
}

void CameraManager::moveCameraLeft() {
	Camera* mainCamera = this->findCameraByName(MAIN_CAMERA);

	if (mainCamera->getMatrix()[3][2] > -21) mainCamera->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f)) * mainCamera->getMatrix());
}

void CameraManager::moveCameraUp() {
	Camera* mainCamera = this->findCameraByName(MAIN_CAMERA);

	if (mainCamera->getMatrix()[3][1] < 24) mainCamera->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * mainCamera->getMatrix());
}

void CameraManager::moveCameraDown() {
	Camera* mainCamera = this->findCameraByName(MAIN_CAMERA);

	if (mainCamera->getMatrix()[3][1] > 6) mainCamera->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f)) * mainCamera->getMatrix());
}

void CameraManager::preGameHandler() {
	this->setNewMainCamera(MAIN_CAMERA);
}

void CameraManager::gameHandler() {
	this->setNewMainCamera(PLAYER_WHITE_CAMERA);
}