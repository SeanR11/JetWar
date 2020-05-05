#pragma once
#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "Game.h"
#include "Player.h"
#include <random>
#include <ctime>

using namespace sf;

class Enemy
{
public:
	Enemy(gameDataRef data);

	void setPosition(float x, float y);
	void move(float x, float y);
	void draw(RenderWindow& window);

	bool isColliding(Player* player);

	Vector2f getPos();
	FloatRect getRect();
	
private:
	gameDataRef _data;
	//float _HP, _Strength;
	Sprite _enemy;
	int randX, planeTypeX, planeTypeY;


};

