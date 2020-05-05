#include "SettingsState.h"



SettingsState::SettingsState(gameDataRef data) : _data(data) {

}

void SettingsState::Init() {

	loadData();

	this->_data->assets.loadTexture("Type1",PLAYER_PATH);
	this->_data->assets.loadTexture("Type2", PLAYER_TYPE_2_PATH);

	this->_background.setTexture(this->_data->assets.getTexture("Main Menu Background"));
	this->_background.setTextureRect({ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT });

	this->_Title.setTexture(this->_data->assets.getTexture("Main Menu Title"));
	this->_Title.setScale(1.5f, 1.5f);
	this->_Title.setPosition(SCREEN_WIDTH / 2 - _Title.getGlobalBounds().width / 2, 0);

	this->_Pointer.setTexture(this->_data->assets.getTexture("Pointer"));

	this->_Text.setFont(this->_data->assets.getFont("TEXT"));
	this->_Text.setString("JET WAR");
	this->_Text.setFillColor(Color::Black);
	this->_Text.setCharacterSize(72);
	this->_Text.setPosition(SCREEN_WIDTH / 2 - _Text.getGlobalBounds().width / 2, _Title.getGlobalBounds().top + _Title.getGlobalBounds().height * 0.8);

	this->_settingsTitle.setFont(this->_data->assets.getFont("TEXT"));
	this->_settingsTitle.setString("Settings");
	this->_settingsTitle.setCharacterSize(HEADLINE * 0.8);
	this->_settingsTitle.setStyle(Text::Underlined);
	this->_settingsTitle.setPosition(SCREEN_WIDTH / 2 - _settingsTitle.getGlobalBounds().width /2 , SCREEN_HEIGHT * 0.3);

	this->_playerTypeTitle.setFont(this->_data->assets.getFont("TEXT"));
	this->_playerTypeTitle.setString("Player type:");
	this->_playerTypeTitle.setCharacterSize(NORMAL);
	this->_playerTypeTitle.setPosition(_settingsTitle.getPosition().x, SCREEN_HEIGHT * 0.5);

	this->_soundTitle.setFont(this->_data->assets.getFont("TEXT"));
	this->_soundTitle.setString("Sound:");
	this->_soundTitle.setCharacterSize(NORMAL);
	this->_soundTitle.setPosition(_settingsTitle.getPosition().x, SCREEN_HEIGHT * 0.5 + 100);
	
	this->_soundStatus.setFont(this->_data->assets.getFont("TEXT"));
	this->_soundStatus.setString("ON");
	this->_soundStatus.setCharacterSize(NORMAL);
	this->_soundStatus.setPosition(_soundTitle.getPosition().x + _soundTitle.getGlobalBounds().width + 1, SCREEN_HEIGHT * 0.5 + 100);

	this->_back.setFont(this->_data->assets.getFont("TEXT"));
	this->_back.setString("Back");
	this->_back.setCharacterSize(NORMAL);
	this->_back.setPosition(_settingsTitle.getPosition().x, SCREEN_HEIGHT * 0.5 + 200);

	this->_playerType.setTexture(this->_data->assets.getTexture("Type1"));
	this->_playerType.setTextureRect(IntRect(150, 100, 98, 150));
	this->_playerType.setPosition(_playerTypeTitle.getPosition().x + _playerTypeTitle.getGlobalBounds().width + 20, _playerTypeTitle.getPosition().y - _playerType.getGlobalBounds().height / 4);
}

void SettingsState::HandleInput() {

	Event eve;
	while (this->_data->window.pollEvent(eve)) {
		if (Event::Closed == eve.type) {
			this->_data->window.close();
		}
		if (Event::KeyPressed == eve.type) {
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				if (selection == 2) {
					if (sound == true)
						sound = false;
					else if (sound == false)
						sound = true;
				}
				if (selection == 3) {
					this->_data->state.isRemoving();
					printFile.open(DATA_FILE);
					printFile << playerType << std::endl << sound;
					printFile.close();
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Down) && selection != 3)
				selection++;
			if (Keyboard::isKeyPressed(Keyboard::Up) && selection != 1)
				selection--;
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
				if (selection == 1 && playerType == 1)
					playerType = 0;
				else if (selection == 1 && playerType == 0)
					playerType = 1;
				if (selection == 2) {
					if (sound == true)
						sound = false;
					else if (sound == false)
						sound = true;
				}
			}
		}
	}
}



void SettingsState::Update(float dt) {

	if (selection == 1) {
		this->_Pointer.setPosition(_playerTypeTitle.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _playerTypeTitle.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);
	}
	else if (selection == 2) {
		this->_Pointer.setPosition(_soundTitle.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _soundTitle.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);

	}
	else  if (selection == 3) {
		this->_Pointer.setPosition(_back.getGlobalBounds().left - _Pointer.getGlobalBounds().width * 1.2, _back.getGlobalBounds().top - _Pointer.getGlobalBounds().height * 0.25);

	}

	if (sound == true) {
		this->_soundStatus.setString("ON");
	}
	else if (sound == false) {
		this->_soundStatus.setString("OFF");
	}

	if (playerType == 1) {
		this->_playerType.setTexture(this->_data->assets.getTexture("Type1"));
		this->_playerType.setTextureRect(IntRect(100, 150, 98, 150));
	}
	else if (playerType == 0)	{
		this->_playerType.setTexture(this->_data->assets.getTexture("Type2"));
		this->_playerType.setTextureRect(IntRect(0, 0, 100, 166));
	}

	backgroundCounter++;
	_background.setTextureRect({ 0 + backgroundCounter, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	if (backgroundCounter > 1500)
		backgroundCounter = 0;
}

void SettingsState::Draw(float dt) {

	this->_data->window.clear();
	this->_data->window.draw(_background);
	this->_data->window.draw(_Title);
	this->_data->window.draw(_Text);
	this->_data->window.draw(_settingsTitle);
	this->_data->window.draw(_back);
	this->_data->window.draw(_soundStatus);
	this->_data->window.draw(_soundTitle);
	this->_data->window.draw(_playerTypeTitle);
	this->_data->window.draw(_playerType);
	this->_data->window.draw(_Pointer);
	this->_data->window.display();
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });

}

int SettingsState::getData(int type) {
	
	if (type == 1) {
		int temp = playerType;
		return temp;
	}
	if (type == 2) {
		int temp = sound;
		return temp;
	}
}

void SettingsState::loadData() {

	readFile.open(DATA_FILE, ifstream::app);
	string temp[2];
	for (int i = 0; i < 2; i++)
		readFile >> temp[i];
	this->playerType = stoi(temp[0]);
	this->sound = stoi(temp[1]);
	readFile.close();
}