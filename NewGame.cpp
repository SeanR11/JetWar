#include "NewGame.h"
#include <Windows.h>
#include "PauseState.h"
#include "GameOverState.h"
#include "SettingsState.h"


NewGame::NewGame(gameDataRef data) : _data(data) {

}

void NewGame::Init() {

	srand(time(NULL));
	SettingsState tempState(_data);
	tempState.loadData();
	playerType = tempState.getData(1);
	sound = tempState.getData(2);
	
	player = new Player(_data,playerType);
	
	_speedRate.restart();
	_generateEnemy.restart();

	timer.setFillColor(Color::Transparent);
	timer.setPosition(SCREEN_WIDTH * 0.8, 25);
	timer.setSize({ 0 , 10 });

	dataBar.setFillColor(Color::Black);
	dataBar.setPosition({ 0,0 });
	dataBar.setSize({ SCREEN_WIDTH,80 });
	dataBar.setOutlineThickness(1.0f);
	dataBar.setOutlineColor(Color::Blue);

	this->_data->assets.loadFont("FONT", MAIN_FONT_PATH);
	this->_score.setFont(this->_data->assets.getFont("FONT"));
	this->_level.setFont(this->_data->assets.getFont("FONT"));
	this->_levelUp.setFont(this->_data->assets.getFont("FONT"));

	this->_score.setCharacterSize(NORMAL);
	this->_score.setPosition({ 25, 40 - 36 / 2 });
	this->_score.setString("Score: " + to_string(score));

	this->_level.setCharacterSize(NORMAL);
	this->_level.setString("Level: " + to_string(lvl));
	this->_level.setPosition({ SCREEN_WIDTH /2  - _level.getGlobalBounds().width /2 , 40 - 36 / 2 });

	this->_data->assets.loadTexture("BACKGROUND", GAME_BACKGROUND_PATH);
	this->_background.setTexture(this->_data->assets.getTexture("BACKGROUND"));
	this->_background.setTextureRect(IntRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	this->_levelUp.setCharacterSize(NORMAL * 1.3);
	this->_levelUp.setString("LEVEL UP!");
	this->_levelUp.setFillColor(Color(255, 255, 255, opacity));
	this->_levelUp.setPosition({ SCREEN_WIDTH / 2 - _levelUp.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _levelUp.getGlobalBounds().height / 2 });

	tempBuffer[0].loadFromFile(MISSLE_LAUNCH_SOUND_PATH);
	this->missle_launch_sound.setBuffer(tempBuffer[0]);

	tempBuffer[1].loadFromFile(MISSLE_HIT_SOUND_PATH);
	this->missle_hit_sound.setBuffer(tempBuffer[1]);

	tempBuffer[2].loadFromFile(ENEMY_PLANE_CRUSH_PATH);
	this->enemy_plane_crush_sound.setBuffer(tempBuffer[2]);

	tempBuffer[3].loadFromFile(ENEMY_PLANE_HIT_PATH);
	this->enemy_plane_hit_sound.setBuffer(tempBuffer[3]);
	
	
}

void NewGame::HandleInput() {

	Event eve;

	while (this->_data->window.pollEvent(eve)) {
		if (Event::Closed == eve.type)
			this->_data->window.close();

		if (Event::KeyReleased == eve.type) {
			if (eve.key.code == Keyboard::Left || eve.key.code == Keyboard::Right || eve.key.code == Keyboard::Space && phase == 1 ||
				eve.key.code == Keyboard::Space && phase == 4)
				phase = 1;
		}
		if (Event::MouseButtonPressed == eve.type) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				player->gotHit(300);
			}
						
		}
		if (Event::KeyPressed == eve.type) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				this->_data->state.isAdding(stateRef(new PauseState(_data,this, sound)), false);
			}
			if (Keyboard::isKeyPressed(Keyboard::O)) {
				score += 1500;
			}
			if (Keyboard::isKeyPressed(Keyboard::P)) {
				lvl++;
				updatePhase();
			}
		}
		
	}
}

void NewGame::Update(float dt) {
	
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		phase = 2;
		if(player->getPos().left > 0)
		player->move(moveSpeed * -1, 0);
	}
	 if (Keyboard::isKeyPressed(Keyboard::Right)) {
		phase = 3;
		if(player->getPos().left < SCREEN_WIDTH - player->getPos().width)
			player->move(moveSpeed, 0);
	}
	 if (Keyboard::isKeyPressed(Keyboard::Up) && player->getPos().top > SCREEN_HEIGHT*0.3) {
		player->move(0, moveSpeed * -1);
	}
	 if (Keyboard::isKeyPressed(Keyboard::Down) && player->getPos().top < SCREEN_HEIGHT - player->getPos().height * 1.5) {
		player->move(0, moveSpeed);
	}
	 if (Keyboard::isKeyPressed(Keyboard::Space) && _speedRate.getElapsedTime().asSeconds() > shootRate && _isReloading == false) {
		 if(phase == 1 && playerType == 1)
			 phase = 4;
		 if (playerType == 2) {
			 shootFlag = true;
			 _shootAnimation.restart();
		 }
		 _missles.push_back(new Missle(_data, *player));
		 _speedRate.restart();
		player->shoot();
		if(sound != 0)
		missle_launch_sound.play();
		
		 if(player->magazinStatus() == 0) {
			 _reload.restart();
			 _isReloading = true;
		 }

		 
	 }

	 for (int i = 0; i < _missles.size(); i++) {
		 if (_missles[i]->getPos().y > 81)
			 _missles[i]->move(0, missleSpeed * -1);
		 if(_missles[i]->getPos().y <= 81){
			 delete _missles[i];
			 _missles.erase(std::remove(_missles.begin(), _missles.end(), _missles[i]), _missles.end());
			 break;
		 }
		 for (int s = 0; s < _enemies.size(); s++) {
			 if (_missles[i]->isCollided(_enemies[s])) {
				 if (sound != 0)
				 this->missle_hit_sound.play();
				 score += scoreGrowth;
				 delete _enemies[s];
				 _missles.erase(std::remove(_missles.begin(), _missles.end(), _missles[i]), _missles.end());
				 _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), _enemies[s]), _enemies.end());
				 break;
			 }
		 }


	 }
	 for (int i = 0; i < _enemies.size(); i++) {
		 if (_enemies[i]->getPos().y < SCREEN_HEIGHT * 0.8)
			 _enemies[i]->move(0, enemyMoveSpeed);
		 if (_enemies[i]->getPos().y >= SCREEN_HEIGHT * 0.8) {
			 if (sound != 0)
			 this->enemy_plane_crush_sound.play();
			 delete _enemies[i];
			 _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), _enemies[i]), _enemies.end());
			 player->gotHit(planeDMG);
			 break;
		 }
		 if (_enemies[i]->isColliding(player)) {
			 if (sound != 0)
			 this->enemy_plane_hit_sound.play();
			 delete _enemies[i];
			 _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), _enemies[i]), _enemies.end());
			 player->gotHit(planeDMG);
			 break;
		 }
	 }

	 if (_isReloading == true) {
		 timer.setFillColor(Color::Green);
		 timer.setSize(Vector2f(timer.getGlobalBounds().width + 180/(reloadTime * 64), timer.getGlobalBounds().height));
		 if (_reload.getElapsedTime().asSeconds() > reloadTime) {
			 _isReloading = false;
			 player->restartMagazin();
			 timer.setFillColor(Color::Transparent);
			 std::cout << dt * 60;
			 timer.setSize({ 0 , 10 });
			
		 }
		 
	 }
	 if (_generateEnemy.getElapsedTime().asSeconds() > spawnRate ) {
		 createEnemy();
		 _generateEnemy.restart();
	 }
	 if (score >= currentLevel) {
		 lvl++;
		 updatePhase();
	 }
	
	this->_score.setString("Score: " + to_string(score));
	this->_level.setString("Level: " + to_string(lvl));

	this->_background.setTextureRect(IntRect(0 , 1236 - this->backgroundCounter, 900, 1080));
	this->backgroundCounter += 1;
	if (this->backgroundCounter >= 1236)
		this->backgroundCounter = 0;

	player->animation(phase, shootFlag);
	if (_shootAnimation.getElapsedTime().asSeconds() > 0.3)
		shootFlag = false;

	if (player->isAlive() == false)
		this->_data->state.isAdding(stateRef(new GameOverState(_data, score)));
}

void NewGame::Draw(float dt) {

	this->_data->window.clear();
	this->_data->window.draw(_background);
	this->_data->window.draw(dataBar);
	this->_data->window.draw(timer);
	this->_data->window.draw(_score);
	this->_data->window.draw(_level);
	player->draw();
	for (int i = 0; i < _missles.size(); i++)
		_missles[i]->draw(); 
	for (int i = 0; i < _enemies.size(); i++)
		_enemies[i]->draw(this->_data->window);
	if (lvlFlag == true) {
		levelUp();
	}
	
	this->_data->window.display();
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // TESTINGS LOG

	
}

void NewGame::createEnemy() {

	this->_enemies.push_back(new Enemy(_data));
}

void NewGame::updatePhase() {

		this->scoreGrowth = scoreGrowth * 1.4;
		this->spawnRate = spawnRate * 0.9;
		this->player->addHP(planeDMG);
		if(lvl != 50)
		currentLevel *= 2.5;
		if (lvl == 4 || lvl == 8 || lvl == 12) {
		this->player->setMagzineMax(1);
		}
		if (lvl % 5 == 0) {
			this->reloadTime *= 0.8;
		}
		std::cout << std::endl << currentLevel;
		
		 for (int i = 0; i < _enemies.size(); i++) {
			 delete _enemies[i];
			 _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), _enemies[i]), _enemies.end());
		 }
		 for (int i = 0; i < _missles.size(); i++) {
			 delete _missles[i];
			 _missles.erase(std::remove(_missles.begin(), _missles.end(), _missles[i]), _missles.end());
		 }
		this->lvlFlag = true;
		this->_opacityTime.restart();
		return;
		

	
}

void NewGame::levelUp() {

	if (opacity < 255 && _opacityTime.getElapsedTime().asSeconds() < 1.5) {
		this->opacity += 0.43;
	}
	if (_opacityTime.getElapsedTime().asSeconds() > 1.5) {
		this->opacity -= 0.43;
	}
	if (this->opacity <= 0) {
		lvlFlag = false;
		opacity = 0;
	}
	this->_levelUp.setFillColor(Color(0, 0, 0, this->opacity));
	this->_data->window.draw(this->_levelUp);
	
}

void NewGame::editSound(int newSound) {

	this->sound = newSound;
}