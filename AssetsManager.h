#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>
using namespace sf;
using namespace std;

class AssetsManager
{
public:
	AssetsManager() { } 
	~AssetsManager() { }

	void loadTexture(string name, string path);
	void loadFont(string name, string path);

	Texture& getTexture(string name);
	Font& getFont(string name);
private:
	map<string, Texture> _textures;
	map<string, Font> _fonts;
};

