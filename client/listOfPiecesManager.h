#pragma once

#include <map>
#include <functional>
#include "listOfPieces.h"
#include "movementManager.h"
#include "onStateUpdate.h"
#include "statusManager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class ListOfPiecesManager : public OnStateUpdateListener
{
public:
	ListOfPiecesManager(const ListOfPiecesManager&) = delete;
	ListOfPiecesManager& operator=(const ListOfPiecesManager&) = delete;
	~ListOfPiecesManager() = default;

	void onStateChangeUpdate(GameStatus) override;

	static ListOfPiecesManager& getInstance();
	bool initialize(ListOfPieces*, ListOfPieces*, Node*);

	void clearLists();
	Piece* getChoosenPiece();

	void moveChooseNodeLeft();
	void moveChooseNodeRight();
	void confirmChoice();
    bool confirmMove();
private:
	ListOfPiecesManager();
	ListOfPieces* getCurrentList() const;
	void moveChooseNode(const int&);
	void preGameHandler();
	void gameHandler();

	MovementManager& m_movementManager;
	StatusManager& m_statusManager;
	std::map<GameStatus, std::function<void()>> m_mapFunctionOnState;
	ListOfPieces* m_whiteList;
	ListOfPieces* m_blackList;
	Node* m_selectPointer;
	Node* m_rootNode;
	int m_iteratorOnList;
};

