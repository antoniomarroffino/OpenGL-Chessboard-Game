#pragma once

#include "test.h"
#include "light.h"

class MockLight : public Light {
public:
	MockLight(const std::string& name = "defaultLight") : Light(name) {}

	MOCK_METHOD(void, render, (const glm::mat4&), (override));
	MOCK_METHOD(const glm::mat4, getFinalMatrix, (), (const, override));
	MOCK_METHOD(const std::vector<Node*>, getChildren, (), (const, override));
};