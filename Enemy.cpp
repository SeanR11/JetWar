#include "Enemy.h"

Enemy::Enemy(gameDataRef data) : _data(data){

	this->_data->assets.loadTexture("Enemy", ENEMY_PATH);

	this->_enemy.setTexture(this->_data->assets.getTexture("Enemy"));

	randX = rand() % 800+5;
	planeTypeX = rand() % 3 + 0;
	planeTypeY = rand() & 1 + 0;
	this->setPosition(randX, 81);
	this->_enemy.setTextureRect(IntRect(98 * planeTypeX, 150 * planeTypeY, 98, 150));
}

void Enemy::setPosition(float x, float y) {

	this->_enemy.setPosition({ x , y });
}

void Enemy::move(float x, float y) {
	this->_enemy.move({ x , y });
}

void Enemy::draw(RenderWindow& window) {

	window.draw(_enemy);
}

bool Enemy::isColliding(Player* player) {

	if (_enemy.getGlobalBounds().intersects(player->getPos()))
		return true;
	else
		return false;
}

Vector2f Enemy::getPos() {
	return this->_enemy.getPosition();
}

FloatRect Enemy::getRect() {

	return this->_enemy.getGlobalBounds();
}
