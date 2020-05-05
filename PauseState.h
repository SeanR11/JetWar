#pragma once
#include "Game.h"
#include "SFML/Graphics.hpp"
#include "Definitions.h"
#include "NewGame.h"

class PauseState : public State
{
public:
	PauseState(gameDataRef data, NewGame *game, int newSound);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:

	gameDataRef _data;
	Sprite _Window;
	RectangleShape _shadow;
	Text _restart, _home, _sound, _soundStatus;
	NewGame * _game;
	bool sound = true;

};

