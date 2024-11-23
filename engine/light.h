#pragma once


#include "node.h"

class Light : public Node {
public:
	Light(const std::string&);
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;
};