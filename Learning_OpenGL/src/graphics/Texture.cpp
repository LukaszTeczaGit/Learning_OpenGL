#include "Texture.h"

#include <iostream>

int Texture::currentId = 0;

Texture::Texture() {}

Texture::Texture(const char* path, const char* name, bool defaultParams) : path(path), name(name), id(currentId++) {
	generate();

	if (defaultParams) {
		setFilters(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		setWrap(GL_REPEAT);
	}
}

void Texture::generate() {
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::load(bool flip = true) {
	stbi_set_flip_vertically_on_load(flip);

	unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
	GLenum colorMode = GL_RGB;



}

void Texture::setFilters(GLenum all) {

}
void Texture::setFilters(GLenum mag, GLenum min) {

}

void Texture::setWrap(GLenum all) {

}
void Texture::setWrap(GLenum s, GLenum t) {

}

void Texture::activate() {

}