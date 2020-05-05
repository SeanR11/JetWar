#include "PauseState.h"
#include "MainMenu.h"
#include "NewGame.h"

PauseState::PauseState(gameDataRef data, NewGame* game, int newSound) : _data(data) {

	this->_game = game;
	this->sound = newSound;
}

void PauseState::Init() {
	std::cout << std::endl << this->sound;
	this->_data->assets.loadTexture("Window", PAUSE_WINDOW_PATH);

	this->_Window.setTexture(this->_data->assets.getTexture("Window"));
	this->_Window.setPosition({ SCREEN_WIDTH / 2 - _Window.getGlobalBounds().width / 2  , SCREEN_HEIGHT / 2 - _Window.getGlobalBounds().height / 2 });

	this->_shadow.setFillColor(Color(199, 199, 200, 2.5));
	this->_shadow.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	this->_data->assets.loadFont("Font", MAIN_FONT_PATH);

	this->_restart.setFont(this->_data->assets.getFont("Font"));
	this->_home.setFont(this->_data->assets.getFont("Font"));
	this->_sound.setFont(this->_data->assets.getFont("Font"));
	this->_soundStatus.setFont(this->_data->assets.getFont("Font"));

	this->_restart.setString("Restart");
	this->_restart.setCharacterSize(NORMAL);
	this->_restart.setPosition(this->_Window.getGlobalBounds().left + this->_Window.getGlobalBounds().width / 2 - _restart.getGlobalBounds().width / 2, this->_Window.getGlobalBounds().top + this->_Window.getGlobalBounds().height * 0.2);

	this->_sound.setString("Sound:");
	this->_sound.setCharacterSize(NORMAL);
	this->_sound.setPosition(_restart.getPosition().x, this->_Window.getGlobalBounds().top + this->_Window.getGlobalBounds().height * 0.5);

	if (this->sound == true)
		this->_soundStatus.setString("ON");
	else
		this->_soundStatus.setString("OFF");
	this->_soundStatus.setCharacterSize(NORMAL);
	this->_soundStatus.setPosition(this->_Window.getGlobalBounds().left + this->_Window.getGlobalBounds().width * 0.7, this->_Window.getGlobalBounds().top + this->_Window.getGlobalBounds().height * 0.5);

	this->_home.setString("Home");
	this->_home.setCharacterSize(NORMAL);
	this->_home.setPosition(_restart.getPosition().x, this->_Window.getGlobalBounds().top + this->_Window.getGlobalBounds().height * 0.8);


}

void PauseState::HandleInput() {

	Event eve;
	while (this->_data->window.pollEvent(eve)) {
		if (Event::Closed == eve.type)
			this->_data->window.close();
		if (Event::KeyPressed == eve.type) {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				_game->editSound(sound);
				this->_data->state.isRemoving();
			}
		}
		if (Event::MouseButtonPressed == eve.type) {
			if (this->_data->input.isTextClicked(_restart, Mouse::Button::Left, this->_data->window))
				this->_data->state.isAdding(stateRef(new NewGame(_data)));
			if (this->_data->input.isTextClicked(_sound, Mouse::Button::Left, this->_data->window)) {
				if (this->sound == true) {
					this->_soundStatus.setString("OFF");
					this->sound = false;
				}
				else if (this->sound == false) {
					this->_soundStatus.setString("ON");
					this->sound = true;
				}
			}
			if (this->_data->input.isTextClicked(_home, Mouse::Button::Left, this->_data->window)) {
				this->_data->state.isAdding(stateRef(new MainMenu(_data)));

			}

		}
	}
}

void PauseState::Update(float dt) {

	if (this->_data->input.isTextCollide(_restart, this->_data->window)) {
		_restart.setFillColor(Color::Cyan);
	}
	else if (this->_data->input.isTextCollide(_sound, this->_data->window)) {
		_sound.setFillColor(Color::Cyan);
	}
	else if (this->_data->input.isTextCollide(_home, this->_data->window)) {
		_home.setFillColor(Color::Cyan);
	}
	else {
		_restart.setFillColor(Color::White);
		_sound.setFillColor(Color::White);
		_home.setFillColor(Color::White);
	}

}
void PauseState::Draw(float dt) {

	this->_data->window.draw(_shadow);
	this->_data->window.draw(_Window);
	this->_data->window.draw(_restart);
	this->_data->window.draw(_sound);
	this->_data->window.draw(_soundStatus);
	this->_data->window.draw(_home);
	this->_data->window.display();
}
