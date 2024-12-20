#include "movementManager.h"

MovementManager::MovementManager() : m_turn{ true } {}

MovementManager::~MovementManager() = default;

MovementManager& MovementManager::getInstance() {
	static MovementManager instance;
	return instance;
}

float MovementManager::getFactoryByTurn() const {
	return m_turn ? 1.0f : -1.0f;
}

void MovementManager::moveRight(Node* node) {
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, MOVEMENT_SPACE * getFactoryByTurn())) * node->getMatrix());
	m_turn = !m_turn;
}

void MovementManager::moveLeft(Node* node) {
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -MOVEMENT_SPACE * getFactoryByTurn())) * node->getMatrix());
	m_turn = !m_turn;
}

void MovementManager::moveUp(Node* node) {
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(MOVEMENT_SPACE * getFactoryByTurn(), 0.0f, 0.0f)) * node->getMatrix());
	m_turn = !m_turn;
}

void MovementManager::moveDown(Node* node) {
	node->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-MOVEMENT_SPACE * getFactoryByTurn(), 0.0f, 0.0f)) * node->getMatrix());
	m_turn = !m_turn;
}