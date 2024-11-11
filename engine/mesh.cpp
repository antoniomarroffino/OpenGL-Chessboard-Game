#include "mesh.h"

Mesh::Mesh(const std::string& name, const std::vector<glm::vec3>& vertices)
	: Node(name), m_vertices{vertices} {}

void Mesh::render(const glm::mat4& matrix) {
	//GLLOAD MATRIX

	//DRAW BY VERTICES
	Node::render(matrix);
}