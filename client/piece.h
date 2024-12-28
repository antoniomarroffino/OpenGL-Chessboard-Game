#pragma once

#include "node.h"

class Piece
{
public:
	Piece(Node*, const unsigned int&, const unsigned int&);
	Piece(const Piece&);
	~Piece() = default;
	Node* getNode() const;
	const unsigned int& getRow() const;
	void setRow(const unsigned int&);
	const unsigned int& getCol() const;
	void setCol(const unsigned int&);
private:
	Node* m_node;
	unsigned int m_row;
	unsigned int m_col;
};

