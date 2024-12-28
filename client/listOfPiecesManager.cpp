#include "listOfPiecesManager.h"
#include "gameManager.h"

unsigned int tempRow = 0;
unsigned int tempCol = 0;
glm::mat4 tempMatrix = glm::mat4(1.0f);

ListOfPiecesManager::ListOfPiecesManager() : OnStateUpdateListener(), m_movementManager{ MovementManager::getInstance() }, m_statusManager{ StatusManager::getInstance() },
m_whiteList{ nullptr }, m_blackList{ nullptr }, m_selectPointer{ nullptr },
m_iteratorOnList{ 0 }, m_rotationAngle{ 1.2f }
{
	this->m_statusManager.subscribeListener(GameStatus::PRE_GAME, this);
	this->m_statusManager.subscribeListener(GameStatus::GAME, this);
}

ListOfPiecesManager& ListOfPiecesManager::getInstance() {
	static ListOfPiecesManager instance;
	return instance;
}

bool ListOfPiecesManager::initialize() {
	this->clearLists();

	this->buildChessboard();

	this->m_iteratorOnList = 0;

	if (!this->m_selectPointer) {
		this->m_selectPointer = const_cast<Node*>(GameManager::getRootNode()->findNodeByName("SelectPointer"));
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

void ListOfPiecesManager::buildChessboard() {
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;

	Node* tempRoot = GameManager::getRootNode();
	std::cout << GameManager::getRootNode() << std::endl;

	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White rook")), 0, 0));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White knight.001")), 0, 1));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White bitshop.001")), 0, 2));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White queen")), 0, 3));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White king")), 0, 4));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White bitshop")), 0, 5));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White knight")), 0, 6));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("White rook.001")), 0, 7));

	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("A")), 1, 0));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("B")), 1, 1));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("C")), 1, 2));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("D")), 1, 3));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("E")), 1, 4));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("F")), 1, 5));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("G")), 1, 6));
	whitePieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("H")), 1, 7));

	this->m_whiteList = new ListOfPieces(whitePieces);

	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black rook.001")), 7, 7));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black knight")), 7, 6));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black bitshop")), 7, 5));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black king")), 7, 4));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black queen")), 7, 3));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black bitshop.001")), 7, 2));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black knight.001")), 7, 1));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("Black rook")), 7, 0));

	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("H.001")), 6, 7));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("G.001")), 6, 6));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("F.001")), 6, 5));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("E.001")), 6, 4));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("D.001")), 6, 3));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("C.001")), 6, 2));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("B.001")), 6, 1));
	blackPieces.push_back(new Piece(const_cast<Node*>(tempRoot->findNodeByName("A.001")), 6, 0));
	
	this->m_blackList = new ListOfPieces(blackPieces);
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
	tempMatrix = this->getChoosenPiece()->getNode()->getMatrix();
}

void ListOfPiecesManager::deleteChoice() {
	this->m_selectPointer->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)) * this->m_selectPointer->getMatrix());

	this->getChoosenPiece()->setCol(tempCol);
	this->getChoosenPiece()->setRow(tempRow);
	this->getChoosenPiece()->getNode()->setMatrix(tempMatrix);

	GameManager::getRootNode()->removeChild(this->m_selectPointer);
	this->m_iteratorOnList = 0;
	this->getCurrentList()->getPieceByIndex(this->m_iteratorOnList)->getNode()->addChild(this->m_selectPointer);
}

bool ListOfPiecesManager::confirmMove() {
	if (this->getChoosenPiece()->getRow() == tempRow && this->getChoosenPiece()->getCol() == tempCol) return false;
	if (this->getCurrentList()->getNumberOfPiecesByCoordinates(this->getChoosenPiece()->getRow(), this->getChoosenPiece()->getCol()) > 1) return false;

	this->m_selectPointer->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.3f, 0.0f)) * this->m_selectPointer->getMatrix());
	GameManager::getRootNode()->removeChild(this->m_selectPointer);

	ListOfPieces* againstListOfPieces = this->getCurrentList() == this->m_whiteList ? this->m_blackList : this->m_whiteList;
	Piece* eatenPiece = againstListOfPieces->getPieceByCoordinates(this->getChoosenPiece()->getRow(), this->getChoosenPiece()->getCol());
	if (eatenPiece != nullptr) {
		GameManager::getRootNode()->removeChild(eatenPiece->getNode());
		againstListOfPieces->removePiece(eatenPiece);
	}

	this->m_iteratorOnList = 0;
	againstListOfPieces->getPieceByIndex(this->m_iteratorOnList)->getNode()->addChild(this->m_selectPointer);
	return true;
}

void  ListOfPiecesManager::preGameHandler() {
	this->m_iteratorOnList = 0;
	GameManager::getRootNode()->removeChild(this->m_selectPointer);
}

void ListOfPiecesManager::gameHandler() {
	this->m_iteratorOnList = 0;
	this->m_whiteList->getPieceByIndex(this->m_iteratorOnList)->getNode()->addChild(this->m_selectPointer);
}

void ListOfPiecesManager::updateSelectPointer() {
	if (this->m_selectPointer != nullptr)
		this->m_selectPointer->setMatrix(this->m_selectPointer->getMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(this->m_rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f)));
}

ListOfPieces* ListOfPiecesManager::getWhitePieces() const {
	return this->m_whiteList;
}

ListOfPieces* ListOfPiecesManager::getBlackPieces() const {
	return this->m_blackList;
}