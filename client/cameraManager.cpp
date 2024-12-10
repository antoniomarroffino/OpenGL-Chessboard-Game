#include "cameraManager.h"

struct CameraManager::Reserved {
	//possibile salvataggio delle camere, esempio map<String, Camera*> e riempite / svuotata ogni add / remove -> meno interpolazioni nell'albero
};

CameraManager::CameraManager() : m_reserved{std::make_unique<CameraManager::Reserved>()} {}

CameraManager& CameraManager::getInstance() {
	static CameraManager instance;
	return instance;
}

CameraManager::~CameraManager() = default;

bool CameraManager::addNewCamera(Camera* newCamera, Node* parentNode) {
	if (newCamera == nullptr || parentNode == nullptr) return false;

	return parentNode->addChild(newCamera);
}

bool CameraManager::removeCamera(const std::string& cameraName, Node* parentNode) {
	if (parentNode == nullptr) return false;

	return parentNode->removeChild(const_cast<Node*>(parentNode->findNodeByName(cameraName)));
}

bool CameraManager::setNewMainCamera(const std::string& cameraName, Node* rootNode) const {
	if (rootNode == nullptr) return false;
	Camera* oldMainCamera = dynamic_cast<Camera*>(rootNode->getMainCamera());
	
	if (oldMainCamera != nullptr) oldMainCamera->setMainCamera(false);

	Camera* newMainCamera = dynamic_cast<Camera*>(const_cast<Node*>(rootNode->findNodeByName(cameraName)));

	if (newMainCamera == nullptr) return false;

	newMainCamera->setMainCamera(true);
	return true;
}

Camera* CameraManager::getMainCamera(const Node* rootNode) const {
	return dynamic_cast<Camera*>(const_cast<Node*>(rootNode->getMainCamera()));
}