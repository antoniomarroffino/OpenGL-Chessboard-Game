#pragma once

#include "memory"
#include "list"
#include "object.h"

class List {
public:
	List(const List&) = delete;
	~List() = default;

	void operator=(const List&) = delete;

	static List& getInstance();
	bool addRowToListOfNodeToRender(Object*, const glm::mat4&);
	void clearList();
	void renderElements(const glm::mat4&) const;
private:
	
	struct Reserved;
	std::unique_ptr<Reserved> reserved;
	std::list<Reserved*> listOfReservedToRender;

	List();
};