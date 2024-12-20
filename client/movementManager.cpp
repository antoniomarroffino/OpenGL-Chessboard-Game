#include "movementManager.h"

MovementManager::MovementManager() : m_turn{ true } {}

MovementManager::~MovementManager() = default;

MovementManager& MovementManager::getInstance() {
	static MovementManager instance;
	return instance;
}

bool MovementManager::getTurn() const {
	return this->m_turn;
}

float MovementManager::getFactoryByTurn() const {
	return this->getTurn() ? 1.0f : -1.0f;
}

void MovementManager::changeTurn() {
	this->m_turn = !this->m_turn;
}

void MovementManager::moveRight(Node* node) {
	if (node == nullptr)
		return;
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, this->MOVEMENT_SPACE * this->getFactoryByTurn())) * node->getMatrix());
}

void MovementManager::moveLeft(Node* node) {
	if (node == nullptr)
		return; 
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -(this->MOVEMENT_SPACE) * this->getFactoryByTurn())) * node->getMatrix());
}

void MovementManager::moveUp(Node* node) {
	if (node == nullptr)
		return; 
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(this->MOVEMENT_SPACE * this->getFactoryByTurn(), 0.0f, 0.0f)) * node->getMatrix());
}

void MovementManager::moveDown(Node* node) {
	if (node == nullptr)
		return;
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-(this->MOVEMENT_SPACE) * this->getFactoryByTurn(), 0.0f, 0.0f)) * node->getMatrix());
}