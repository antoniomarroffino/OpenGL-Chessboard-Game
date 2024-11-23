#pragma once


#include "object.h"
#include "texture.h"

class ENG_API Material : public Object {
public:
	Material(const std::string&);
	void render(const glm::mat4 & = glm::mat4(1.0f)) override;

private:
	Texture* m_texture;
};