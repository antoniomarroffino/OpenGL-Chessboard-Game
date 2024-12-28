#include "historyManager.h"
#include "gameManager.h"

struct HistoryManager::Reserved {
	ListOfPieces* listOfPiecesWhite;
	ListOfPieces* listOfPiecesBlack;
	Node* rootNode;

	Reserved(ListOfPieces* piecesWhite, ListOfPieces* piecesBlack, Node* root) :
		listOfPiecesWhite{ piecesWhite },
		listOfPiecesBlack{ piecesBlack },
		rootNode{root} {}
};

HistoryManager::HistoryManager() : m_history(std::vector<HistoryManager::Reserved>()), 
		m_currentRootNode{nullptr},
		m_listOfPiecesManager{ListOfPiecesManager::getInstance()},
		m_pointer{ -1 } { }

HistoryManager& HistoryManager::getInstance() {
	static HistoryManager instance;
	return instance;
}

void HistoryManager::saveState() {
	Reserved reserved{ Reserved(this->m_listOfPiecesManager.getWhitePieces()->clone(),
		this->m_listOfPiecesManager.getBlackPieces()->clone(),
		GameManager::getRootNode()->clone())
	};
	this->m_history.push_back(reserved);
	this->m_pointer++;
}

bool HistoryManager::undo() {
	if (this->m_pointer == 0)
		return false;
	this->m_pointer--;

	GameManager::setRootNode(this->m_history[this->m_pointer].rootNode);
	this->m_listOfPiecesManager.initialize();
	return true;
}

bool HistoryManager::redo() {
	return true;
}