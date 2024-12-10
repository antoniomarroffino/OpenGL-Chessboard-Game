#include "texture.h"

Texture::Texture(const std::string& name) : Object(name) { }

void Texture::render(const glm::mat4& matrix) {
	//WRAP REPEAT PER S e T PER OGNI TEXTURE
	//set x2 glTexParameteri sia MIN che MAX
}

