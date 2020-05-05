#include "Missle.h"


Missle::Missle(gameDataRef data, Player & player) : _data(data) {

	missleText.loadFromFile(PLAYER_PATH);
	_Missle.setTexture(missleText);
	_Missle.setTextureRect(IntRect(206, 78, 9, 49));
	setPosition(player);



}

void Missle::draw() {

	this->_data->window.draw(_Missle);

}

void Missle::setPosition(Player & player) {
	
	Vector2f pos;
	pos.x =(player.getPos().left + player.getPos().width / 2 )- _Missle.getGlobalBounds().width /2;
	pos.y = player.getPos().top - _Missle.getGlobalBounds().height;
	_Missle.setPosition(pos);
}

void Missle::move(float x, float y) {
	_Missle.move(x, y);
}

Vector2f Missle::getPos() {
	return _Missle.getPosition();
}

bool Missle::isCollided(Enemy * enemy) {
	

	if (_Missle.getGlobalBounds().intersects(enemy->getRect())) {
		return true;
	}
	else {
		return false;
	}
}