/**
 * @file		list.h
 * @brief	Concrete List include file
 *
 * @author	Luca Fantò (C) SUPSI [luca.fanto@student.supsi.ch]
 * @author	Mattia Cainarca (C) SUPSI [mattia.cainarca@student.supsi.ch]
 * @author	Antonio Marroffino (C) SUPSI [antonio.marroffino@student.supsi.ch]
 */
#pragma once

 //////////////
 // #INCLUDE //
 //////////////

	// C/C++:
#include "node.h"
#include <memory>
#include <list>


 ///////////////////////
 // MAIN LIST CLASS //
 ///////////////////////

 /**
  * @brief Base List class
  */
class ENG_API List{
public:
	List();
	~List();
	List(const List&) = delete;
	void operator=(const List&) = delete;

	void pass(const Node*);
	void clearList();
	void renderElements(const glm::mat4&) const;
	const unsigned int getNumberOfElementsInList() const;
private:
	void addRowToListOfNodeToRender(Node*);
	void resetListAndFreeMemory();

	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
	std::list<Reserved*> m_listOfReservedToRender;
};