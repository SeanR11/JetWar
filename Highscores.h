#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Definitions.h"
#include <fstream>

class Highscores : public State
{
public:
	Highscores(gameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	void loadHighscores();
	int checkHighscores(int newScore);
	void orderHighscore(int start);
	int getHighscore();
	void updateHighscores();

private:
	gameDataRef _data;
	Sprite _background, _Title, _Pointer;
	Text _Text,_highscoreTitle, _highscores[5], _back;

	int backgroundCounter = 0;
	string highscoresArray[5];

	ofstream printFile;
	ifstream readFile;
};

