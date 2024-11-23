#pragma once


#include "object.h"

class Texture : public Object {
public:
	Texture(const std::string&);
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;

};