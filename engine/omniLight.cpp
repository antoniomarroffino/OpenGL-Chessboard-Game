#include "omniLight.h"

ENG_API OmniLight::OmniLight(const std::string& name) : Light(name) {}

void ENG_API OmniLight::render(const glm::mat4& matrix) {

}

const unsigned int OmniLight::parse(const char* data, unsigned int& position) {
	const unsigned int& children = Node::parse(data, position);
	return children;
}