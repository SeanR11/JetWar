#include "SplashState.h"
#include "MainMenu.h"

#include "GameOverState.h"

SplashState::SplashState(gameDataRef data) : _data(data) {

}

void SplashState::Init() {

	this->_data->assets.loadTexture("Background", SPLASH_BACKGROUND_PATH);

	_background.setTexture(this->_data->assets.getTexture("Background"));

}

void SplashState::HandleInput() {

	Event ent;
	while (this->_data->window.pollEvent(ent)) {
		if (Event::Closed == ent.type)
			this->_data->window.close();
	}
}

void SplashState::Update(float dt) {

	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_TIME) {
		//switch state;
		this->_data->state.isAdding(stateRef(new MainMenu(_data)));
		return;
	}

}

void SplashState::Draw(float dt) {

	this->_data->window.clear();
	this->_data->window.draw(this->_background);
	this->_data->window.display();
}
