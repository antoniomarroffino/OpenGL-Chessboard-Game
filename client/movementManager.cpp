#include "movementManager.h"

MovementManager::MovementManager() : m_turn{ true }, m_statusManager{StatusManager::getInstance()}, m_mapFunctionOnState{std::map<GameStatus, std::function<void()>>()}
{
	this->m_statusManager.subscribeListener(GameStatus::PRE_GAME, this);
	this->m_mapFunctionOnState[GameStatus::PRE_GAME] = [this]() {this->preGameHandler();};
}

MovementManager::~MovementManager() = default;

MovementManager& MovementManager::getInstance() {
	static MovementManager instance;
	return instance;
}

void MovementManager::onStateChangeUpdate(GameStatus gameState) {
	auto it = this->m_mapFunctionOnState.find(gameState);
	if (it != this->m_mapFunctionOnState.end() && it->second != nullptr)
		it->second();
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

void MovementManager::moveRight(Piece* piece) {
	if (piece == nullptr) return;

	if (this->getTurn()) {
		if (piece->getCol() == 7) return;
	}
	else {
		if (piece->getCol() == 0) return;
	}

	piece->getNode()->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, this->MOVEMENT_SPACE * this->getFactoryByTurn())) * piece->getNode()->getMatrix());

	piece->setCol(piece->getCol() + (1 * (int)this->getFactoryByTurn()));
}

void MovementManager::moveLeft(Piece* piece) {
	if (piece == nullptr) return;

	if (this->getTurn()) {
		if (piece->getCol() == 0) return;
	}
	else {
		if (piece->getCol() == 7) return;
	}


	piece->getNode()->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -(this->MOVEMENT_SPACE) * this->getFactoryByTurn())) * piece->getNode()->getMatrix());

	piece->setCol(piece->getCol() - (1 * (int)this->getFactoryByTurn()));
}

void MovementManager::moveUp(Piece* piece) {
	if (piece == nullptr) return;

	if (this->getTurn()) {
		if (piece->getRow() == 7) return;
	}
	else {
		if (piece->getRow() == 0) return;
	}

	piece->getNode()->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(this->MOVEMENT_SPACE * this->getFactoryByTurn(), 0.0f, 0.0f)) * piece->getNode()->getMatrix());

	piece->setRow(piece->getRow() + (1 * (int)this->getFactoryByTurn()));
}

void MovementManager::moveDown(Piece* piece) {
	if (piece == nullptr) return;

	if (this->getTurn()) {
		if (piece->getRow() == 0) return;
	}
	else {
		if (piece->getRow() == 7) return;
	}

	piece->getNode()->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(-(this->MOVEMENT_SPACE) * this->getFactoryByTurn(), 0.0f, 0.0f)) * piece->getNode()->getMatrix());

	piece->setRow(piece->getRow() - (1 * (int)this->getFactoryByTurn()));
}

void MovementManager::preGameHandler() {
	this->m_turn = true;
}