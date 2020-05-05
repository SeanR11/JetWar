#include "Highscores.h"
#include <Windows.h>
Highscores::Highscores(gameDataRef data) : _data(data) {

}

void Highscores::Init() {

	this->_background.setTexture(this->_data->assets.getTexture("Main Menu Background"));
	this->_background.setTextureRect({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	
	this->_Pointer.setTexture(this->_data->assets.getTexture("Pointer"));

	this->_Title.setTexture(this->_data->assets.getTexture("Main Menu Title"));
	this->_Title.setScale(1.5f, 1.5f);
	this->_Title.setPosition(SCREEN_WIDTH / 2 - _Title.getGlobalBounds().width / 2, 0);
	
	this->_Text.setFont(this->_data->assets.getFont("TEXT"));
	this->_Text.setString("JET WAR");
	this->_Text.setFillColor(Color::Black);
	this->_Text.setCharacterSize(72);
	this->_Text.setPosition(SCREEN_WIDTH / 2 - _Text.getGlobalBounds().width / 2, _Title.getGlobalBounds().top + _Title.getGlobalBounds().height * 0.8);

	this->_highscoreTitle.setFont(this->_data->assets.getFont("TEXT"));
	this->_highscoreTitle.setString("Highscores");
	this->_highscoreTitle.setCharacterSize(HEADLINE * 0.8);
	this->_highscoreTitle.setStyle(Text::Underlined);
	this->_highscoreTitle.setPosition(SCREEN_WIDTH / 2 - _highscoreTitle.getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.3);

	loadHighscores();
	
	for (int i = 0; i < 5; i++) {
		_highscores[i].setFont(this->_data->assets.getFont("TEXT"));
		_highscores[i].setCharacterSize(NORMAL);
	}

	this->_highscores[0].setString("1." + highscoresArray[0]);
	this->_highscores[1].setString("2." + highscoresArray[1]);
	this->_highscores[2].setString("3." + highscoresArray[2]);
	this->_highscores[3].setString("4." + highscoresArray[3]);
	this->_highscores[4].setString("5." + highscoresArray[4]);

	this->_highscores[0].setPosition(SCREEN_WIDTH / 2 - _highscores[0].getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.4 + 80 * 0);
	this->_highscores[1].setPosition(SCREEN_WIDTH / 2 - _highscores[0].getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.4 + 80 * 1);
	this->_highscores[2].setPosition(SCREEN_WIDTH / 2 - _highscores[0].getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.4 + 80 * 2);
	this->_highscores[3].setPosition(SCREEN_WIDTH / 2 - _highscores[0].getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.4 + 80 * 3);
	this->_highscores[4].setPosition(SCREEN_WIDTH / 2 - _highscores[0].getGlobalBounds().width / 2, SCREEN_HEIGHT * 0.4 + 80 * 4);

	this->_back.setFont(this->_data->assets.getFont("TEXT"));
	this->_back.setString("Back");
	this->_back.setCharacterSize(NORMAL);
	this->_back.setPosition(SCREEN_WIDTH/2 - _back.getGlobalBounds().width/2, _highscores[4].getPosition().y + 100);

	this->_Pointer.setPosition(_back.getPosition().x - _Pointer.getGlobalBounds().width, _back.getPosition().y - _Pointer.getGlobalBounds().height * 0.25);

}

void Highscores::HandleInput() {

	Event eve;
	while (this->_data->window.pollEvent(eve)) {
		if (Event::Closed == eve.type) {
			this->_data->window.close();
		}
		if (Event::KeyPressed == eve.type) {
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				this->_data->state.isRemoving();
		}
	}
}
void Highscores::Update(float dt) {

	backgroundCounter++;
	this->_background.setTextureRect({ 0 + backgroundCounter++, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	if (backgroundCounter >= 1500)
		backgroundCounter = 0;

}
void Highscores::Draw(float dt) {

	this->_data->window.clear();
	this->_data->window.draw(_background);
	this->_data->window.draw(_Pointer);
	this->_data->window.draw(_Title);
	this->_data->window.draw(_Text);
	this->_data->window.draw(_highscoreTitle);
	for (int i = 0; i < 5; i++) {
		this->_data->window.draw(_highscores[i]);
	}
	this->_data->window.draw(_back);
	this->_data->window.display();
}

void Highscores::loadHighscores() {

	readFile.open("Resources/data/highscores.dll");
	for (int i = 0; i < 5; i++) {
		readFile >> this->highscoresArray[i];
	}
}

int Highscores::checkHighscores(int newScore) {

	int number;
	for (int i = 0; i < 5; i++) {
		if (newScore > stoi(highscoresArray[i])) {
			number = i + 1;
			orderHighscore(i);
			this->highscoresArray[i] =  to_string(newScore);
			updateHighscores();
			break;
		}
		else
			number = 0;
	}
	return number;
}

void Highscores::updateHighscores() {

	printFile.open("Resources/data/highscores.dll");
	for (int i = 0; i < 5; i++) {
		printFile << this->highscoresArray[i] << std::endl;
	}
}

void Highscores::orderHighscore(int start){

	string temp[5];
	for (int i = 0; i < 5; i++)
		temp[i] = this->highscoresArray[i];
	this->highscoresArray[start] = "0";
	for (int i = start + 1; i < 5 - start + 1; i++)
		this->highscoresArray[i] = temp[i - 1];

}

int Highscores::getHighscore() {
	int temp = stoi(this->highscoresArray[0]);
	return temp;
}
