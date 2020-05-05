#pragma once
#include "Definitions.h"
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"

using namespace sf;

class Missle
{
public:
	Missle(gameDataRef data, Player & player);

	void setPosition( Player& player);
	void move(float x, float y);
	void draw();
	//void shoot(float missleSpeed);
	Vector2f getPos();
	bool isCollided(Enemy *enemy);
private:
	gameDataRef _data;
	Sprite _Missle;
	Texture missleText;
	int strength = 10;

	RectangleShape tem;


	

};

