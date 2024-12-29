#include "lightManager.h"
#include "gameManager.h"

LightManager::LightManager() : m_lights{std::vector<Light*>()} {}

LightManager& LightManager::getInstance() {
	static LightManager instance;
	return instance;
}

void LightManager::turnOn(const std::string& lightName, Node* parent) {
	if (parent == nullptr) parent = GameManager::getRootNode();

	Light* lightToTurnOn = this->isLightPresent(lightName);
	if (lightToTurnOn == nullptr) return;

	parent->addChild(lightToTurnOn);
}

void LightManager::turnOff(const std::string& lightName, Node* parent) {
	if (parent == nullptr) parent = GameManager::getRootNode();

	Light* light = dynamic_cast<Light*>(const_cast<Node*>(parent->findNodeByName(lightName)));
	if (light == nullptr) return;

	if (this->isLightPresent(lightName) == nullptr)
		this->m_lights.push_back(light);

	parent->removeChild(light);
}

bool LightManager::isLightOn(const std::string& lightName, Node* parent) const {
	if (parent == nullptr) parent = GameManager::getRootNode();
	return parent->findNodeByName(lightName) != nullptr;
}

void LightManager::increaseLight(const std::string& lightName, Node* parent) {
	if (parent == nullptr) parent = GameManager::getRootNode();

	Light* light = dynamic_cast<Light*>(const_cast<Node*>(parent->findNodeByName(lightName)));
	if (light == nullptr) return;

	light->increaseIntensity();
}

void LightManager::decreaseLight(const std::string& lightName, Node* parent) {
	if (parent == nullptr) parent = GameManager::getRootNode();

	Light* light = dynamic_cast<Light*>(const_cast<Node*>(parent->findNodeByName(lightName)));
	if (light == nullptr) return;

	light->decreaseIntensity();
}

Light* LightManager::isLightPresent(const std::string& lightName) const {
	for (auto* light : this->m_lights)
		if (light->getName() == lightName)
			return light;
	return nullptr;
}