#pragma once
#include "Definitions.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Missle.h"
#include <random>

class NewGame : public State
{
public:
	NewGame();
	NewGame(gameDataRef data);

	void Init();
	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

	void createEnemy();
	void updatePhase();
	void levelUp();
	void editSound(int newSound);

private:

	gameDataRef _data;
	Player* player;
	Text _score, _level, _levelUp;
	Sprite _background;
	RectangleShape timer, dataBar;

	Clock _speedRate, _reload, _generateEnemy, _opacityTime, _shootAnimation;

	vector<Missle*> _missles;
	vector<Enemy*> _enemies;

	SoundBuffer tempBuffer[4];
	Sound missle_launch_sound, missle_hit_sound, enemy_plane_crush_sound, enemy_plane_hit_sound;

	int phase = 1;
	int planeDMG = 75;
	float opacity = 0;
	int playerType = 1, sound = 1;
	bool lvlFlag = false, shootFlag = false;
	float shootRate = 0.7f, reloadTime = 2.5f, spawnRate = 3.5f ;
	int score = 0, scoreGrowth = 10;
	int currentLevel = LEVEL_1;
	int lvl = 1;
	bool _isReloading = false;
	int moveSpeed = 4.0f, missleSpeed = 2.0f;
	int enemyMoveSpeed = 1.0f;
	int backgroundCounter = 0;
};

