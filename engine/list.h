#pragma once

#include "iList.h"
#include "memory"
#include "list"

class ENG_API List : public IList {
public:
	List();
	~List() override;
	List(const List&) = delete;
	void operator=(const List&) = delete;

	void pass(const Node*) override;
	void clearList() override;
	void renderElements(const glm::mat4&) const override;
private:
	bool addRowToListOfNodeToRender(Object*, const glm::mat4&);
	void resetListAndFreeMemory();
	
	struct Reserved;
	std::unique_ptr<Reserved> reserved;
	std::list<Reserved*> listOfReservedToRender;
};