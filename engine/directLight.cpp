#include "directLight.h"

ENG_API DirectLight::DirectLight(const std::string& name) : Light(name) {}

void ENG_API DirectLight::render(const glm::mat4& matrix) {

}

const unsigned int DirectLight::parse(const char* data, unsigned int& position) {
	const unsigned int& children = Node::parse(data, position);
	return children;
}