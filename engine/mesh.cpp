#include "mesh.h"

Mesh::Mesh(std::string name, std::vector<glm::vec3> vertices)
	: Node(name), m_vertices{vertices} 
{
}

void Mesh::render(glm::mat4 matrix) {
	//GLLOAD MATRIX

	//DRAW BY VERTICES
	Node::render(matrix);
}