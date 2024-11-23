#pragma once

#include "iList.h"
#include "memory"
#include "list"
#include "object.h"

class ENG_API List : public IList {
public:
	List();
	~List() override = default;
	List(const List&) = delete;
	void operator=(const List&) = delete;

	bool addRowToListOfNodeToRender(Object*, const glm::mat4&) override;
	void clearList() override;
	void renderElements(const glm::mat4&) const override;
private:
	
	struct Reserved;
	std::unique_ptr<Reserved> reserved;
	std::list<Reserved*> listOfReservedToRender;
};