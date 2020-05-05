#include "AssetsManager.h"

void AssetsManager::loadTexture(string name, string path) {

	Texture temp;
	if(temp.loadFromFile(path))
	this->_textures[name] = temp;
}

void AssetsManager::loadFont(string name, string path) {

	Font temp;
	if (temp.loadFromFile(path))
		this->_fonts[name] = temp;
}

Texture& AssetsManager::getTexture(string name) {
	return _textures[name];
}
Font& AssetsManager::getFont(string name) {
	return _fonts[name];
}
