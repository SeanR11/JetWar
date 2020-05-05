#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "InputManager.h"
#include "AssetsManager.h"
#include "StateManager.h"

struct gameData {

	AssetsManager assets;
	InputManager	input;
	StateManager state;
	RenderWindow window;

};

typedef std::shared_ptr<gameData> gameDataRef;

class Game
{
public:
	Game(int Width, int Height, string Title);
private:
	const float dt = 1.0f / 60.0f;

	Clock _clock;
	gameDataRef _data = make_shared<gameData>();

	void run();
};

