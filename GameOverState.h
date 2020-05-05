#pragma once
#include "SFML/Graphics.hpp"	
#include "Definitions.h"
#include "Game.h"

class GameOverState : public State
{
public:

	GameOverState(gameDataRef data, int score);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	gameDataRef _data;
	Text _retry, _home, _scoreTitle, _score, _recordTitle, _record, _newRecord, _GO;
	Sprite _Window;
	RectangleShape _shadow;

	int highscoreNumber;
	//Highscores* highscore;

};

