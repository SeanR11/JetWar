#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Definitions.h"
#include "SettingsState.h"


class MainMenu : public State
{
public:
	MainMenu(gameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);
	void Resume();

	void loadSound();

private:
	gameDataRef _data;
	Sprite _Background, _Title, _Pointer;
	Text _Text, _Newgame, _Highscore, _Settings, _Exit;
	int backgroundCounter = 0;
	int selection = 0;
	int lineSpace = 100;
	bool tempSound;
	SettingsState* state;
	RectangleShape rect;
	Music backgroundMusic;

};

