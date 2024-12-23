#pragma once

#include <map>
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

	static ListOfPiecesManager& getInstance();
	bool initialize(ListOfPieces*, ListOfPieces*, Node*);

	void clearLists();
	Piece* getChoosenPiece();

	void moveChooseNodeLeft();
	void moveChooseNodeRight();
	void confirmChoice();
	void deleteChoice();
	bool confirmMove();
	void updateSelectPointer();
private:
	ListOfPiecesManager();
	ListOfPieces* getCurrentList() const;
	void moveChooseNode(const int&);
	void preGameHandler() override;
	void gameHandler() override;

	MovementManager& m_movementManager;
	StatusManager& m_statusManager;
	ListOfPieces* m_whiteList;
	ListOfPieces* m_blackList;
	Node* m_selectPointer;
	Node* m_rootNode;
	int m_iteratorOnList;
	float m_rotationAngle;
};

