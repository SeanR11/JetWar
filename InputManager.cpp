#include "InputManager.h"

bool InputManager::isSpriteClicked(Sprite object, Mouse::Button key, RenderWindow& window) {

	if (Mouse::isButtonPressed(key)) {
		IntRect temp(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (temp.contains(getMousePosition(window)))
			return true;
		else
			return false;
	}	

}

bool InputManager::isTextCollide(Text text, RenderWindow& window) {
	IntRect temp(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);
	if (temp.contains(getMousePosition(window)))
		return true;
	else
	return false;
}

bool InputManager::isTextClicked(Text text, Mouse::Button button, RenderWindow& window) {
	
	if (Mouse::isButtonPressed(button)) {
		IntRect temp(text.getPosition().x, text.getPosition().y, text.getGlobalBounds().width, text.getGlobalBounds().height);
		if (temp.contains(getMousePosition(window)))
			return true;
		else
			return false;
	}
	else
		return false;
}

Vector2i InputManager::getMousePosition(RenderWindow &window) {

	return Mouse::getPosition(window);
}
