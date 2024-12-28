#include "historyManager.h"
#include "gameManager.h"

struct HistoryManager::Reserved {
	ListOfPieces* listOfPiecesWhite;
	ListOfPieces* listOfPiecesBlack;

	Reserved(ListOfPieces* piecesWhite, ListOfPieces* piecesBlack) :
		listOfPiecesWhite{ piecesWhite },
		listOfPiecesBlack{ piecesBlack }
		{}
};

HistoryManager::HistoryManager() : m_history(std::vector<HistoryManager::Reserved>()),
		m_listOfPiecesManager{ListOfPiecesManager::getInstance()},
		m_movementManager{MovementManager::getInstance()},
		m_statusManager{StatusManager::getInstance()},
		m_pointer{ 0 }, m_undoCalled{ false } 
{
	this->m_statusManager.subscribeListener(GameStatus::CHOICE, this);
}

HistoryManager& HistoryManager::getInstance() {
	static HistoryManager instance;
	return instance;
}

void HistoryManager::choiceHandler() {
	if(!this->isUndoCalled())
		this->takeSnapshot();
}

void HistoryManager::takeSnapshot() {
	Reserved reserved{ Reserved(this->m_listOfPiecesManager.getWhitePieces()->clone(),
		this->m_listOfPiecesManager.getBlackPieces()->clone())
	};
	this->m_history.push_back(reserved);
	std::cout << "take snap pointer: " << this->m_pointer << std::endl;
	this->m_pointer++;
}

bool HistoryManager::undo() {
	if (this->m_pointer == 0)
		return false;
	if (this->isUndoCalled())
		this->m_pointer--;
	else
		this->m_pointer -= 2;
	std::cout << "undo pointer: " << this->m_pointer << std::endl;
	this->m_movementManager.changeTurn();
	this->m_listOfPiecesManager.updateChessboard(this->m_history[this->m_pointer].listOfPiecesWhite, this->m_history[this->m_pointer].listOfPiecesBlack);
	GameManager::getRootNode()->removeChild(const_cast<Node*>(GameManager::getRootNode()->findNodeByName("SelectPointer")));
	this->m_undoCalled = true;
	return true;
}

bool HistoryManager::redo() {
	return true;
}

bool HistoryManager::isUndoCalled() {
	return this->m_undoCalled;
}

void HistoryManager::setUndoCalled(const bool& val) {
	this->m_undoCalled = val;
}