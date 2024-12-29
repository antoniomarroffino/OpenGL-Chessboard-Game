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
	bool initialize();

	Piece* getChoosenPiece();

	void moveChooseNodeLeft();
	void moveChooseNodeRight();
	void confirmChoice();
	void deleteChoice();
	bool confirmMove();
	void updateSelectPointer();

	ListOfPieces* getWhitePieces() const;
	ListOfPieces* getBlackPieces() const;
	void updateChessboard(ListOfPieces*, ListOfPieces*);
private:
	ListOfPiecesManager();
	ListOfPieces* getCurrentList() const;
	void moveChooseNode(const int&);
	void preGameHandler() override;
	void choiceHandler() override;
	void endGameHandler() override;
	void buildChessboard();
	void clearLists();
	void createShadow();

	MovementManager& m_movementManager;
	StatusManager& m_statusManager;
	ListOfPieces* m_whiteList;
	ListOfPieces* m_blackList;
	Node* m_selectPointer;
	int m_iteratorOnList;
	float m_rotationAngle;
};

