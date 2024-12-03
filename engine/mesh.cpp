#include "mesh.h"

Mesh::Mesh(const std::string& name)
	: Node(name) {}

void Mesh::render(const glm::mat4& matrix) {
	//GLLOAD MATRIX

	//DRAW BY VERTICES
	Node::render(matrix);
}

const unsigned int Mesh::parse(const char* data, unsigned int& position) {
	const unsigned int& children = Node::parse(data, position);
	return children;
}