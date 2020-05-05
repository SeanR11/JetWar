#pragma once
#include "Game.h"
#include "Definitions.h"
#include "SFML/Graphics.hpp"

class SplashState : public State
{
public:

	SplashState(gameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);


private:
	Clock _clock;
	Sprite _background;
	gameDataRef _data;
};

