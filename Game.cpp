#include "Game.h"
#include "SplashState.h"
#include <Windows.h>

Game::Game(int Width, int Height, string Title) {

	this->_data->window.create(VideoMode(Width, Height), Title, Style::Titlebar | Style::Close);

	this->_data->state.isAdding(stateRef(new SplashState(this->_data)));
	this->run();
}

void Game::run() {

	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen()) {

		this->_data->state.processStateChanges();

		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime > 0.25f) {
			frameTime = 0.25f;
		}
		currentTime = newTime;
		accumulator += frameTime;
		if (accumulator > this->dt) {
			this->_data->state.GetActiveState()->HandleInput();
			this->_data->state.GetActiveState()->Update(this->dt);
			accumulator -= this->dt;
		}
		
		interpolation = accumulator / this->dt;
		this->_data->state.GetActiveState()->Draw(this->dt);

		//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); // TESTINGS LOG
	}
}
