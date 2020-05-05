#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class InputManager
{
public:
	InputManager(){ }
	~InputManager(){ }

	bool isSpriteClicked(Sprite object, Mouse::Button button, RenderWindow& window);
	bool isTextCollide(Text text, RenderWindow& window);
	bool isTextClicked(Text text, Mouse::Button button, RenderWindow& window);
	Vector2i getMousePosition(RenderWindow& window);
};

