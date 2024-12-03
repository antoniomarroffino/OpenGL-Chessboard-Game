#include "spotLight.h"

ENG_API SpotLight::SpotLight(const std::string& name) : Light(name) {}

void ENG_API SpotLight::render(const glm::mat4& matrix) {

}

const unsigned int SpotLight::parse(const char* data, unsigned int& position) {
	const unsigned int& children = Node::parse(data, position);
	return children;
}