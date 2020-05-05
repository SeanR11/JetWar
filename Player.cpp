#include "Player.h"

Player::Player(gameDataRef data, int type) : _data(data){

	this->magzinClip.loadFromFile(PLAYER_PATH);

	playerType = type;
	if (playerType == 1) {
		this->playerText.loadFromFile(PLAYER_PATH);

		this->_player.setTexture(playerText);
		this->_player.setTextureRect(IntRect(99, 150, 99, 150));
	}
	if (playerType == 0) {
		this->playerText.loadFromFile(PLAYER_TYPE_2_PATH);

		this->_player.setTexture(playerText);
		this->_player.setTextureRect(IntRect(0, 0, 100, 166));
	}
	setPosition(SCREEN_WIDTH / 2 - this->_player.getGlobalBounds().width , SCREEN_HEIGHT * 0.8 - this->_player.getGlobalBounds().height/ 2);

	this->_magzinClip.setTexture(magzinClip);
	this->_magzinClip.setTextureRect(IntRect(206, 78, 9, 49));

	this->hpBar.setFillColor(Color::Green);
	this->hpBarCover.setFillColor(Color::Red);

	this->hpBar.setSize({ 70,3});
	this->hpBarCover.setSize({ 70,3});

	this->hpBar.setPosition(_player.getPosition().x + _player.getGlobalBounds().width/2 - hpBar.getGlobalBounds().width /2,
							_player.getPosition().y + _player.getGlobalBounds().height + hpBar.getGlobalBounds().height / 2);
	this->hpBarCover.setPosition(_player.getPosition().x + _player.getGlobalBounds().width / 2 - hpBarCover.getGlobalBounds().width / 2,
		_player.getPosition().y + _player.getGlobalBounds().height + hpBarCover.getGlobalBounds().height / 2);
}

void Player::setPosition(float x, float y) {

	this->_player.setPosition({ x , y });
}

void Player::draw() {

	this->_magzinClip.setPosition(SCREEN_WIDTH * 0.7, 15);

	this->_data->window.draw(this->_player);
	this->_data->window.draw(this->hpBarCover);
	this->_data->window.draw(this->hpBar);
	for (int i = 0; i < this->magazinStatus(); i++) {
		this->_data->window.draw(this->_magzinClip);
		this->_magzinClip.move({ this->_magzinClip.getGlobalBounds().width * 4, 0 });
	}


	
}

void Player::move(float x, float y) {
	this->_player.move(x, y);
	this->hpBar.move(x, y);
	this->hpBarCover.move(x, y);
}

void Player::animation(int phase, bool shoot) {

	if (playerType == 1) {
		if (phase == 1) {
			this->_player.setTextureRect(IntRect(99, 150, 99, 150));
		}
		if (phase == 2) {
			this->_player.setTextureRect(IntRect(0, 150, 99, 150));
		}
		if (phase == 3) {
			this->_player.setTextureRect(IntRect(198, 150, 99, 150));
		}
		if (phase == 4) {
			this->_player.setTextureRect(IntRect(0, 0, 99, 150));
		}
	}
	if (playerType == 0) {
		if (shoot == false) {
			if (phase == 1) {
				this->_player.setTextureRect(IntRect(0, 0, 100, 166));
			}
			if (phase == 2) {
				this->_player.setTextureRect(IntRect(100, 0, 100, 166));
			}
			if (phase == 3) {
				this->_player.setTextureRect(IntRect(300, 0, 100, 166));
			}
		}
		if (shoot == true) {
			if (phase == 1) {
				this->_player.setTextureRect(IntRect(0, 166, 100, 166));
			}
			if (phase == 2) {
				this->_player.setTextureRect(IntRect(100, 166, 100, 166));
			}
			if (phase == 3) {
				this->_player.setTextureRect(IntRect(300, 166,100, 166));
			}

		}
	}
}
void Player::setPlayerType(int type) {

	playerType = type;
	if (playerType == 1) {
		this->playerText.loadFromFile(PLAYER_PATH);

		this->_player.setTexture(playerText);
	}
	if (playerType == 0) {
		this->playerText.loadFromFile(PLAYER_TYPE_2_PATH);

		this->_player.setTexture(playerText);
	}
}
void Player::gotHit(float dmg) {

	if (this->cHP > 0)
		cHP -= dmg;
	this->hpBar.setSize({ MAX_BAR * (this->cHP / this->mHP), hpBar.getGlobalBounds().height });

}

void Player::addHP(int amount) {
	if (this->cHP == this->mHP)
		return;
	this->cHP += amount;
	this->hpBar.setSize({ MAX_BAR * (this->cHP / this->mHP), hpBar.getGlobalBounds().height });
	
}

bool Player::isAlive() {
	if (this->cHP > 0)
		return true;
	else
		return false;
}
void Player::shoot() {
	_magzine--;
}
void Player::restartMagazin() {
	_magzine = _magzineMax;
}
int Player::magazinStatus() {

		return _magzine;
}
void Player::setMagzineMax(int max) {
	_magzineMax += max;
}
FloatRect Player::getPos() {
	return this->_player.getGlobalBounds();
}
