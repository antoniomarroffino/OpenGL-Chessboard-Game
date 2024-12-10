#include "texture.h"

ENG_API Texture::Texture(const std::string& name) : Object(name) { }

void ENG_API Texture::render(const glm::mat4& matrix) {
	//WRAP REPEAT PER S e T PER OGNI TEXTURE
	//set x2 glTexParameteri sia MIN che MAX
}

const ENG_API unsigned int Texture::parse(const char* data, unsigned int& position) {
	//CARICAMENTO BITMAP
	/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, bitmap);
	*/
}