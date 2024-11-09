#pragma once

#include "node.h"

class Mesh : public Node {
public:
	Mesh(std::string, std::vector<glm::vec3>);
	void render(glm::mat4) override;
private:
	std::vector<glm::vec3> m_vertices;
};