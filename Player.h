#pragma once
#include "Definitions.h"
#include "SFML/Graphics.hpp"
#include "Game.h"

using namespace sf;

class Player
{
public:
	Player(gameDataRef data, int type);

	void setPosition(float x, float y);
	void move(float x, float y);
	void gotHit(float dmg);
	void animation(int phase, bool shoot = false);
	void draw();
	void shoot();
	void restartMagazin();
	void setMagzineMax(int max);
	int magazinStatus();
	void setPlayerType(int type);
	void addHP(int amount);
	bool isAlive();
	FloatRect getPos();
private:

	gameDataRef _data;
	Sprite _player, _magzinClip;
	Texture playerText, magzinClip;
	RectangleShape hpBar, hpBarCover;
	int _magzine = 5, _magzineMax = 5;
	float cHP = 300;
	float mHP = 300;
	float MAX_BAR = 70;
	int playerType = 2;


};

