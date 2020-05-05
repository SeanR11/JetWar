#include "MainMenu.h"
#include "NewGame.h"
#include "Highscores.h"

MainMenu::MainMenu(gameDataRef data) : _data(data) {
	state = new SettingsState(_data);
}

void MainMenu::Init() {

	backgroundMusic.openFromFile(MUSIC_PATH);
	backgroundMusic.setPlayingOffset(seconds(4.0f));
	backgroundMusic.setLoop(true);
	loadSound();
	this->_data->assets.loadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_PATH);
	this->_data->assets.loadTexture("Main Menu Title", MAIN_MENU_TITLE_PATH);
	this->_data->assets.loadTexture("Pointer", POINTER_PATH);

	this->_Background.setTexture(this->_data->assets.getTexture("Main Menu Background"));
	this->_Title.setTexture(this->_data->assets.getTexture("Main Menu Title"));
	this->_Pointer.setTexture(this->_data->assets.getTexture("Pointer"));

	this->_Title.setScale(1.5f, 1.5f);
	this->_Title.setPosition(SCREEN_WIDTH / 2 - _Title.getGlobalBounds().width / 2, 0);

	this->_Background.setTextureRect(IntRect(0, 0, 900, 1080));

	this->_data->assets.loadFont("TEXT", MAIN_FONT_PATH);

	this->_Text.setFont(this->_data->assets.getFont("TEXT"));
	this->_Newgame.setFont(this->_data->assets.getFont("TEXT"));
	this->_Highscore.setFont(this->_data->assets.getFont("TEXT"));
	this->_Settings.setFont(this->_data->assets.getFont("TEXT"));
	this->_Exit.setFont(this->_data->assets.getFont("TEXT"));

	this->_Text.setString("JET WAR");
	this->_Text.setFillColor(Color::Black);
	this->_Text.setCharacterSize(72);
	this->_Text.setPosition(SCREEN_WIDTH / 2 - _Text.getGlobalBounds().width / 2, _Title.getGlobalBounds().top + _Title.getGlobalBounds().height * 0.8);

	this->_Newgame.setString("New Game");
	this->_Newgame.setCharacterSize(NORMAL);
	this->_Newgame.setPosition(SCREEN_WIDTH / 2 - _Newgame.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.4 - _Newgame.getGlobalBounds().height / 2);

	this->_Highscore.setString("Highscore");
	this->_Highscore.setCharacterSize(NORMAL);
	this->_Highscore.setPosition(SCREEN_WIDTH / 2 - _Highscore.getGlobalBounds().width / 2, _Newgame.getGlobalBounds().top + _Highscore.getGlobalBounds().height + lineSpace);

	this->_Settings.setString("Settings");
	this->_Settings.setCharacterSize(NORMAL);
	this->_Settings.setPosition(SCREEN_WIDTH / 2 - _Settings.getGlobalBounds().width / 2, _Highscore.getGlobalBounds().top + _Settings.getGlobalBounds().height + lineSpace);

	this->_Exit.setString("Exit");
	this->_Exit.setCharacterSize(NORMAL);
	this->_Exit.setPosition(SCREEN_WIDTH / 2 - _Exit.getGlobalBounds().width / 2, _Settings.getGlobalBounds().top + _Exit.getGlobalBounds().height + lineSpace);

	
	this->rect.setOutlineColor(Color::Red);
	this->rect.setOutlineThickness(1.0f);
	this->rect.setFillColor(Color::Transparent);

	float length = _Pointer.getGlobalBounds().width;
	float high = _Pointer.getLocalBounds().height;
	this->rect.setSize(Vector2f(length,high));
}

void MainMenu::HandleInput() {

	Event eve;

	while (this->_data->window.pollEvent(eve)) {
		if (Event::Closed == eve.type)
			this->_data->window.close();
		if (Event::KeyPressed == eve.type) {
			if (Keyboard::isKeyPressed(Keyboard::Down) && selection != 3) {
				selection++;

				
			}
			if (Keyboard::isKeyPressed(Keyboard::Up) && selection != 0) {
				selection--;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				if (selection == 0) {
					this->_data->state.isAdding(stateRef(new NewGame(_data)));
					//general.stop();
					backgroundMusic.stop();
					
				}
				if (selection == 1) {
					this->_data->state.isAdding(stateRef(new Highscores(_data)), false);
				}
				if (selection == 2) {
					this->_data->state.isAdding(stateRef(new SettingsState(_data)), false);
				}
				if (selection == 3) {
					this->_data->window.close();
				}
			}
		}

	}
}

void MainMenu::Update(float dt) {

	this->_Background.setTextureRect(IntRect(0 + this->backgroundCounter, 0, 900, 1080));
	this->backgroundCounter += 1;
	if (this->backgroundCounter >= 1500)
		this->backgroundCounter = 0;

	if (this->selection == 0) 
		this->_Pointer.setPosition(_Newgame.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _Newgame.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);
	else if (this->selection == 1) 
		this->_Pointer.setPosition(_Highscore.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _Highscore.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);
	else if(this-> selection == 2)
		this->_Pointer.setPosition(_Settings.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _Settings.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);
	else if(this-> selection == 3)
		this->_Pointer.setPosition(_Exit.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _Exit.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);

	rect.setPosition(_Pointer.getPosition().x, _Pointer.getPosition().y);
	


}

void MainMenu::Draw(float dt) {

	this->_data->window.clear();
	this->_data->window.draw(_Background);
	this->_data->window.draw(_Title);
	this->_data->window.draw(_Text);
	this->_data->window.draw(_Newgame);
	this->_data->window.draw(_Highscore);
	this->_data->window.draw(_Settings);
	this->_data->window.draw(_Exit);
	this->_data->window.draw(_Pointer);
	//this->_data->window.draw(rect);
	this->_data->window.display();
}

void MainMenu::loadSound() {
	state->loadData();
	tempSound = state->getData(2);
	if (tempSound == true && backgroundMusic.getStatus() != 2)
		backgroundMusic.play();
	if (tempSound == false)
		backgroundMusic.pause();

}

void MainMenu::Resume() {
	loadSound();
}
