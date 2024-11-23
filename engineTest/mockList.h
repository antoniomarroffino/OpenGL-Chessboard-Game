#pragma once

#include "test.h"
#include "iList.h"

class MockList : public IList {
public:
	MOCK_METHOD(bool, addRowToListOfNodeToRender, (Object*, const glm::mat4&), (override));
	MOCK_METHOD(void, clearList, (), (override));
	MOCK_METHOD(void, renderElements, (const glm::mat4&), (const, override));
};
