#pragma once

#include <vector>
#include <algorithm>
#include "piece.h"

class ListOfPieces
{
public:
	ListOfPieces(const std::vector<Piece*>&);

	ListOfPieces* clone();
	bool removePiece(Piece*);
	void clearList();
	int getSize() const;
	Piece* getPieceByIndex(const unsigned int&) const;
	Piece* getPieceByCoordinates(const unsigned int&, const unsigned int&) const;
	unsigned int getNumberOfPiecesByCoordinates(const unsigned int&, const unsigned int&) const;
private:
	ListOfPieces(const ListOfPieces&);

	std::vector<Piece*> m_listOfPieces;
};

