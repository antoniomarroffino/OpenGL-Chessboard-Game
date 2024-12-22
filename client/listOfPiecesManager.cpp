#include "listOfPiecesManager.h"

unsigned int tempRow = 0;
unsigned int tempCol = 0;


ListOfPiecesManager::ListOfPiecesManager() : OnStateUpdateListener(), m_movementManager{MovementManager::getInstance()}, m_statusManager{StatusManager::getInstance()},
m_whiteList{nullptr}, m_blackList{nullptr}, m_selectPointer{ nullptr }, m_rootNode{nullptr}, 
m_iteratorOnList{ 0 } 
{
	this->m_statusManager.subscribeListener(GameStatus::PRE_GAME, this);
	this->m_statusManager.subscribeListener(GameStatus::GAME, this);
}

ListOfPiecesManager& ListOfPiecesManager::getInstance() {
	static ListOfPiecesManager instance;
	return instance;
}

bool ListOfPiecesManager::initialize(ListOfPieces* whiteList, ListOfPieces* blackList, Node* rootNode) {
	this->m_whiteList = whiteList;
	this->m_blackList = blackList;
	this->m_rootNode = rootNode;

	if (!this->m_whiteList || !this->m_blackList || !this->m_rootNode) return false;

	if (!this->m_selectPointer) {
		this->m_selectPointer = const_cast<Node*>(this->m_rootNode->findNodeByName("SelectPointer"));
		if (!this->m_selectPointer) return false;

		if (this->m_selectPointer != nullptr)
			this->m_selectPointer->setMatrix(
				glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.3f, 2.0f)) *
				glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.3f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::mat4(1.0f));
	}


	return true;
}

void ListOfPiecesManager::clearLists() {
	if (this->m_blackList == nullptr || this->m_whiteList == nullptr) return;

	this->m_whiteList->clearList();
	this->m_blackList->clearList();
}

Piece* ListOfPiecesManager::getChoosenPiece() {
	return this->getCurrentList()->getPieceByIndex(this->m_iteratorOnList);
}

ListOfPieces* ListOfPiecesManager::getCurrentList() const {
	return this->m_movementManager.getTurn() ? this->m_whiteList : this->m_blackList;
}

void ListOfPiecesManager::moveChooseNodeLeft() {
	this->moveChooseNode(-1);
}

void ListOfPiecesManager::moveChooseNodeRight() {
	this->moveChooseNode(1);
}

void ListOfPiecesManager::moveChooseNode(const int& sign) {
	ListOfPieces* currentList = this->getCurrentList();
	currentList->getPieceByIndex(this->m_iteratorOnList)->getNode()->removeChild(this->m_selectPointer);

	this->m_iteratorOnList += sign * 1;
	if (this->m_iteratorOnList < 0) this->m_iteratorOnList = currentList->getSize() - 1;
	else if (this->m_iteratorOnList > currentList->getSize() - 1) this->m_iteratorOnList = 0;

	currentList->getPieceByIndex(this->m_iteratorOnList)->getNode()->addChild(this->m_selectPointer);
}

void ListOfPiecesManager::confirmChoice() {
	this->m_selectPointer->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.3f, 0.0f)) * this->m_selectPointer->getMatrix());

	tempRow = this->getChoosenPiece()->getRow();
	tempCol = this->getChoosenPiece()->getCol();
}

bool ListOfPiecesManager::confirmMove() {
	if (this->getChoosenPiece()->getRow() == tempRow && this->getChoosenPiece()->getCol() == tempCol) return false;
	if (this->getCurrentList()->getNumberOfPiecesByCoordinates(this->getChoosenPiece()->getRow(), this->getChoosenPiece()->getCol()) > 1) return false;

	this->m_selectPointer->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)) * this->m_selectPointer->getMatrix());
	this->m_rootNode->removeChild(this->m_selectPointer);

	ListOfPieces* againstListOfPieces = this->getCurrentList() == this->m_whiteList ? this->m_blackList : this->m_whiteList;
	Piece* eatenPiece = againstListOfPieces->getPieceByCoordinates(this->getChoosenPiece()->getRow(), this->getChoosenPiece()->getCol());
	if (eatenPiece != nullptr) {
		this->m_rootNode->removeChild(eatenPiece->getNode());
		againstListOfPieces->removePiece(eatenPiece);
	}

	this->m_iteratorOnList = 0;
	againstListOfPieces->getPieceByIndex(this->m_iteratorOnList)->getNode()->addChild(this->m_selectPointer);
	return true;
}

void  ListOfPiecesManager::preGameHandler() {
	this->m_iteratorOnList = 0;
	this->m_rootNode->removeChild(this->m_selectPointer);
}

void ListOfPiecesManager::gameHandler() {
	this->m_iteratorOnList = 0;
	this->m_whiteList->getPieceByIndex(this->m_iteratorOnList)->getNode()->addChild(this->m_selectPointer);
}