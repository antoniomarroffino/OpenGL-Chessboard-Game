#pragma once

#include "node.h"

class Mesh : public Node {
public:
	Mesh(const std::string&, const std::vector<glm::vec3>&);
	void render(const glm::mat4&) override;
private:
	std::vector<glm::vec3> m_vertices;
};