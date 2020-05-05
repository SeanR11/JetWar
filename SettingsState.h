#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "Game.h"	
#include "Windows.h"
#include <fstream>

class SettingsState : public State
{
public:
	SettingsState(gameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	int getData(int type);
	void loadData();
private:
	gameDataRef _data;
	Sprite _background, _playerType, _Title, _Pointer;
	Text _Text,_settingsTitle, _playerTypeTitle, _back, _soundTitle, _soundStatus;
	ifstream readFile;
	ofstream printFile;
	bool sound = true, playerType = 1;
	int backgroundCounter = 0;
	int selection = 1;

};

